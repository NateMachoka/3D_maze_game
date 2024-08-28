#include "render.h"
#include <SDL2/SDL.h>
#include "player.h"
#include "maze.h"

/**
 * draw_maze - Draws the maze on the renderer.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 * @maze: The 2D array representing the maze.
 * @maze_width: The width of the maze.
 * @maze_height: The height of the maze.
 * @tile_size: The size of each tile.
 */
void draw_maze(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size) {
    for (int y = 0; y < maze_height; ++y) {
        for (int x = 0; x < maze_width; ++x) {
            SDL_Color color;
            if (maze[y][x] == 1) {
                // Set color to black for walls
                color.r = 0;
                color.g = 0;
                color.b = 0;
                color.a = 255;
            } else if (x == 1 && y == 1) {
                // Set color to green for entry point
                color.r = 0;
                color.g = 255;
                color.b = 0;
                color.a = 255;
            } else if (x == MAZE_WIDTH - 2 && y == MAZE_HEIGHT - 2) {
                // Set color to red for exit point
                color.r = 255;
                color.g = 0;
                color.b = 0;
                color.a = 255;
            } else {
                // Set color to white for paths
                color.r = 255;
                color.g = 255;
                color.b = 255;
                color.a = 255;
            }
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_Rect rect = { x * tile_size, y * tile_size, tile_size, tile_size };
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Draw the boundary around the maze
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue boundary
    SDL_RenderDrawLine(renderer, 0, 0, maze_width * tile_size, 0); // Top boundary
    SDL_RenderDrawLine(renderer, 0, 0, 0, maze_height * tile_size); // Left boundary
    SDL_RenderDrawLine(renderer, maze_width * tile_size - 1, 0, maze_width * tile_size - 1, maze_height * tile_size); // Right boundary
    SDL_RenderDrawLine(renderer, 0, maze_height * tile_size - 1, maze_width * tile_size, maze_height * tile_size - 1); // Bottom boundary
}

/**
 * render - Renders the current state of the game.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 * @maze: The 2D array representing the maze.
 * @maze_width: The width of the maze.
 * @maze_height: The height of the maze.
 * @tile_size: The size of each tile.
 * @player: Pointer to the Player object.
 */
void render(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size, Player *player) {
    clear_screen(renderer);
    draw_maze(renderer, maze, maze_width, maze_height, tile_size);
    draw_player(renderer, player);
    SDL_RenderPresent(renderer);
}

/**
 * clear_screen - Clears the screen with a given color.
 * @renderer: The SDL renderer to draw with.
 */
void clear_screen(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer); // Clear the screen with the chosen color
}
