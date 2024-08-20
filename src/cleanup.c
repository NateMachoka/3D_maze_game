#include <SDL2/SDL.h>
#include "cleanup.h"

/**
 * cleanup - Cleans up resources and quits SDL
 * @renderer: Pointer to SDL_Renderer to be destroyed
 * @window: Pointer to SDL_Window to be destroyed
 */
void cleanup(SDL_Renderer *renderer, SDL_Window *window)
{
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }

    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}
