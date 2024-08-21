#include <SDL2/SDL.h>
#include "init.h"
#include "cleanup.h"
#include "events.h"
#include "render.h"

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

    if (init_sdl(&window, &renderer) != 0)
    {
        return 1;
    }

    Player player;
    SDL_Color player_color = {255, 0, 0, 255};
    init_player(&player, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 25, 25, player_color);

    event_loop(renderer, &player);
    cleanup(renderer, window);

    return 0;
}
