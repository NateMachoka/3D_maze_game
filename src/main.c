#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "config.h"
#include "init.h"
#include "cleanup.h"
#include "events.h"
#include "render.h"
#include "maze.h"
#include "player.h"
#include "sound.h"
#include "raycasting.h"
#include "texture_utils.h"
#include "timer.h"

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

    generate_maze(maze);
    place_start_end(maze);

    if (init_sdl(&window, &renderer) != 0)
    {
        return (1);
    }

    /* Initialize SDL_ttf and load font */
    if (init_ttf() != 0)
    {
        cleanup(renderer, window);
        return 1;
    }
    font = load_font("assets/mesy_guako.ttf", 16);
    if (font == NULL)
    {
        cleanup(renderer, window);
        return 1;
    }
    textColor = (SDL_Color){255, 255, 255, 255}; // White color

    /* Initialize SDL_mixer for audio */
    if (init_audio() != 0)
    {
        cleanup(renderer, window);
        return 1;
    }

    /* Load textures */
    SDL_Texture *wall_texture = load_texture(renderer, "assets/Mayan_wall");
    if (wall_texture == NULL)
    {
        fprintf(stderr, "Error loading wall texture\n");
        cleanup(renderer, window);
        return 1;
    }

    /* Initialize player */
    Player player;
    SDL_Color player_color = {255, 0, 255, 255};
    init_player(&player, tile_size, tile_size, tile_size, tile_size, player_color);

    /* Start the game and timer */
    start_game();

    event_loop(renderer, &player, maze, tile_size, wall_texture);

    /* Clean up resources before exiting */
    SDL_DestroyTexture(wall_texture);
    cleanup(renderer, window);

    return (0);
}
