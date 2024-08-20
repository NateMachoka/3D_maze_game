#include <SDL2/SDL.h>
#include "events.h"
#include "render.h"

/**
 * event_loop - Handles the main event loop of the program
 */

void event_loop(void)
{
	int running = 1;
	SDL_Event event;

	while (running)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = 0;
			}
		}
		render();
	}
}
