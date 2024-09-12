#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "cleanup.h"
#include "init.h"

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

	/* Close audio if initialized */
	Mix_CloseAudio();

	/* Close font and quit TTF if initialized */
	if (font != NULL) {
		TTF_CloseFont(font);
	}
	TTF_Quit();

	SDL_Quit();
}
