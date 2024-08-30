#include "render.h"
#include <SDL2/SDL.h>
#include "player.h"
#include "maze.h"

/**
 * draw_maze - Draws the maze on the renderer with different thicknesses for walls and paths.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 * @maze: The 2D array representing the maze.
 * @maze_width: The width of the maze.
 * @maze_height: The height of the maze.
 * @tile_size: The size of each tile.
 */
void draw_maze(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size)
{
    int path_size = tile_size;
    int wall_size = tile_size / 2;

    for (int y = 0; y < maze_height; ++y) {
        for (int x = 0; x < maze_width; ++x) {
            SDL_Color color;
            SDL_Rect rect;

            if (maze[y][x] == 1) {
                // Wall
                color.r = 0;
                color.g = 0;
                color.b = 0;
                color.a = 255;

                rect.x = x * tile_size + (tile_size - wall_size) / 2;
                rect.y = y * tile_size + (tile_size - wall_size) / 2;
                rect.w = wall_size;
                rect.h = wall_size;
            } else if (x == 1 && y == 1) {
                // Entry Point
                color.r = 0;
                color.g = 255;
                color.b = 0;
                color.a = 255;

                rect.x = x * tile_size + (tile_size - path_size) / 2;
                rect.y = y * tile_size + (tile_size - path_size) / 2;
                rect.w = path_size;
                rect.h = path_size;
            } else if (x == maze_width - 2 && y == maze_height - 2) {
                // Exit Point
                color.r = 255;
                color.g = 0;
                color.b = 0;
                color.a = 255;

                rect.x = x * tile_size + (tile_size - path_size) / 2;
                rect.y = y * tile_size + (tile_size - path_size) / 2;
                rect.w = path_size;
                rect.h = path_size;
            } else {
                // Path
                color.r = 255;
                color.g = 255;
                color.b = 255;
                color.a = 255;

                rect.x = x * tile_size;
                rect.y = y * tile_size;
                rect.w = path_size;
                rect.h = path_size;
            }

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

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
void clear_screen(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer); // Clear the screen with the chosen color
}
