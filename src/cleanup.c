#include <SDL2/SDL.h>
#include "cleanup.h"

/**
 * cleanup - Cleans up resources and quits SDL
 */
void cleanup(SDL_Renderer *renderer, SDL_Window *window)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}
