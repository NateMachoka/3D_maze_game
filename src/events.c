#include <SDL2/SDL.h>
#include "events.h"
#include "render.h"
#include "player.h"
#include "maze.h"

extern int maze[MAZE_HEIGHT][MAZE_WIDTH];

/**
 * event_loop - Handles the main event loop of the program
 * @renderer: Pointer to SDL_Renderer used for rendering
 */
void event_loop(SDL_Renderer *renderer, Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size)
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
            move_player(player, player->pos.x, player->pos.y - 5, maze, tile_size);
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            move_player(player, player->pos.x, player->pos.y + 5, maze, tile_size);
        }
        if (state[SDL_SCANCODE_LEFT])
        {
            move_player(player, player->pos.x - 5, player->pos.y, maze, tile_size);
        }
        if (state[SDL_SCANCODE_RIGHT])
        {
            move_player(player, player->pos.x + 5, player->pos.y, maze, tile_size);
        }
        render(renderer, maze, MAZE_WIDTH, MAZE_HEIGHT, tile_size, player);
    }
}
