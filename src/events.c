#include <SDL2/SDL.h>
#include "events.h"
#include "render.h"

/**
 * event_loop - Handles the main event loop of the program
 * @renderer: Pointer to SDL_Renderer used for rendering
 */
void event_loop(SDL_Renderer *renderer)
{
    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        render(renderer);
    }
}
