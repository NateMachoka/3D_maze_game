#include <SDL2/SDL.h>
#include "render.h"
#include "player.h"
#include "maze.h"
/**
 * render - Renders the current state of the game
 * @renderer: Pointer to SDL_Renderer used for rendering
 */

void render(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size, Player *player)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_maze(renderer, maze, maze_width, maze_height, tile_size);
	draw_player(renderer, player);

	SDL_RenderPresent(renderer);
}
