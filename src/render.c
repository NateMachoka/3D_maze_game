#include "render.h"
#include <SDL2/SDL.h>
#include "player.h"
#include <stdlib.h>
#include <time.h>
#include "maze.h"


/**
 * generate_maze - Generates a maze using a randomized depth-first search algorithm
 * @maze: The 2D array representing the maze
 * @width: The width of the maze
 * @height: The height of the maze
 */
void generate_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH], int width, int height) {
    // Initialize the maze with all walls
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            maze[y][x] = 1;
        }
    }

    // Function to implement the randomized depth-first search
    void carve_passages(int cx, int cy) {
        int directions[] = { 0, 1, 2, 3 };
        // Shuffle directions
        for (int i = 0; i < 4; i++) {
            int r = rand() % 4;
            int temp = directions[r];
            directions[r] = directions[i];
            directions[i] = temp;
        }

        for (int i = 0; i < 4; i++) {
            int dx = 0, dy = 0;
            switch (directions[i]) {
                case 0: dx = 1; break;
                case 1: dy = 1; break;
                case 2: dx = -1; break;
                case 3: dy = -1; break;
            }
            int nx = cx + dx * 2;
            int ny = cy + dy * 2;

            if (nx >= 0 && ny >= 0 && nx < width && ny < height && maze[ny][nx] == 1) {
                maze[cy + dy][cx + dx] = 0;
                maze[ny][nx] = 0;
                carve_passages(nx, ny);
            }
        }
    }

    // Start carving passages from the top-left corner
    maze[1][1] = 0;
    carve_passages(1, 1);
}

/**
 * draw_maze - Draws the maze on the renderer
 * @renderer: Pointer to SDL_Renderer used for rendering
 * @maze: The 2D array representing the maze
 * @maze_width: The width of the maze
 * @maze_height: The height of the maze
 * @tile_size: The size of each tile
 */
void draw_maze(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size) {
    for (int y = 0; y < maze_height; ++y) {
        for (int x = 0; x < maze_width; ++x) {
            if (maze[y][x] == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for walls
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for paths
            }
            SDL_Rect rect = { x * tile_size, y * tile_size, tile_size, tile_size };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Draw the boundary around the maze
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue boundary for contrast with red player
    SDL_RenderDrawLine(renderer, 0, 0, maze_width * tile_size, 0); // Top boundary
    SDL_RenderDrawLine(renderer, 0, 0, 0, maze_height * tile_size); // Left boundary
    SDL_RenderDrawLine(renderer, maze_width * tile_size - 1, 0, maze_width * tile_size - 1, maze_height * tile_size); // Right boundary
    SDL_RenderDrawLine(renderer, 0, maze_height * tile_size - 1, maze_width * tile_size, maze_height * tile_size - 1); // Bottom boundary
}

/**
 * render - Renders the current state of the game
 * @renderer: Pointer to SDL_Renderer used for rendering
 * @maze: The 2D array representing the maze
 * @maze_width: The width of the maze
 * @maze_height: The height of the maze
 * @tile_size: The size of each tile
 * @player: Pointer to the Player object
 */
void render(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size, Player *player) {
    clear_screen(renderer);
    draw_maze(renderer, maze, maze_width, maze_height, tile_size);
    draw_player(renderer, player);
    SDL_RenderPresent(renderer);
}

/**
 * clear_screen - Clears the screen with a given color
 * @renderer: The SDL renderer to draw with
 */
void clear_screen(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer); // Clear the screen with the chosen color
}

/**
 * main - Example of using the maze generation and rendering
 */
int main() {
    // Initialize SDL, create window and renderer, etc.
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize player, maze, etc.
    Player player = { .x = 1, .y = 1 };
    int maze[MAZE_HEIGHT][MAZE_WIDTH];
    int tile_size = 10;

    // Seed random number generator
    srand(time(NULL));

    // Generate the maze
    generate_maze(maze, MAZE_WIDTH, MAZE_HEIGHT);

    // Main game loop
    int running = 1;
    while (running) {
        // Handle input, update game state, etc.

        // Render the maze and player
        render(renderer, maze, MAZE_WIDTH, MAZE_HEIGHT, tile_size, &player);

        SDL_Delay(1000 / 60); // Cap the frame rate at 60 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
