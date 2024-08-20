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

    event_loop(renderer);
    cleanup(renderer, window);

    return 0;
}
