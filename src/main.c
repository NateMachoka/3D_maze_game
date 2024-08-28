#include "config.h"
#include <SDL2/SDL.h>
#include "init.h"
#include "cleanup.h"
#include "events.h"
#include "render.h"
#include "maze.h"

/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    const int tile_size = TILE_SIZE;
    int maze[MAZE_HEIGHT][MAZE_WIDTH];

    // Generate and initialize the maze with start and end points
    generate_maze(maze);
    place_start_end(maze);

    // Initialize SDL components
    if (init_sdl(&window, &renderer) != 0)
    {
        return (1);
    }

    // Initialize player
    Player player;
    SDL_Color player_color = {255, 0, 0, 255}; // Red
    init_player(&player, tile_size, tile_size, tile_size, tile_size, player_color);

    // Start the event loop
    event_loop(renderer, &player, maze, tile_size);

    // Clean up resources before exiting
    cleanup(renderer, window);

    return (0);
}
