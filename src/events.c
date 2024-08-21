#include <SDL2/SDL.h>
#include "events.h"
#include "render.h"
#include "player.h"

/**
 * event_loop - Handles the main event loop of the program
 * @renderer: Pointer to SDL_Renderer used for rendering
 */
void event_loop(SDL_Renderer *renderer, Player *player)
{
    int running;
    SDL_Event event;
    const Uint8 *state;

    running = 1;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
	state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_UP])
	{
		move_player(player, player->pos.x, player->pos.y - 5);
        }
        if (state[SDL_SCANCODE_DOWN])
	{
		move_player(player, player->pos.x, player->pos.y + 5);
        }
        if (state[SDL_SCANCODE_LEFT])
	{
		move_player(player, player->pos.x - 5, player->pos.y);
        }
        if (state[SDL_SCANCODE_RIGHT])
	{
		move_player(player, player->pos.x + 5, player->pos.y);
        }
	render(renderer, player);
    }
}
