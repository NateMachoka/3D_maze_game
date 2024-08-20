#include <SDL2/SDL.h>
#include "render.h"

/**
 * render - Renders the current state of the game
 * @renderer: Pointer to SDL_Renderer used for rendering
 */

void render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}
