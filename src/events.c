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
	int running = 1;
	SDL_Event event;
	const Uint8 *state;
	double move_speed = 0.1; // Player movement speed
	double rot_speed = 0.05; // Player rotation speed

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
			if (maze[(int)(player->pos.y)][(int)(player->pos.x + player->direction.x * move_speed)] == 0)
				player->pos.x += player->direction.x * move_speed;
			if (maze[(int)(player->pos.y + player->direction.y * move_speed)][(int)(player->pos.x)] == 0)
				player->pos.y += player->direction.y * move_speed;
		}
		if (state[SDL_SCANCODE_DOWN])
		{
			if (maze[(int)(player->pos.y)][(int)(player->pos.x - player->direction.x * move_speed)] == 0)
				 player->pos.x -= player->direction.x * move_speed;
			if (maze[(int)(player->pos.y - player->direction.y * move_speed)][(int)(player->pos.x)] == 0)
				player->pos.y -= player->direction.y * move_speed;
		}
		if (state[SDL_SCANCODE_LEFT])
		{
			double old_dir_x = player->direction.x;
			player->direction.x = player->direction.x * cos(-rot_speed) - player->direction.y * sin(-rot_speed);
			player->direction.y = old_dir_x * sin(-rot_speed) + player->direction.y * cos(-rot_speed);
			double old_plane_x = player->plane.x;
			player->plane.x = player->plane.x * cos(-rot_speed) - player->plane.y * sin(-rot_speed);
			player->plane.y = old_plane_x * sin(-rot_speed) + player->plane.y * cos(-rot_speed);
		}
		if (state[SDL_SCANCODE_RIGHT])
		{
			double old_dir_x = player->direction.x;
			player->direction.x = player->direction.x * cos(rot_speed) - player->direction.y * sin(rot_speed);
			player->direction.y = old_dir_x * sin(rot_speed) + player->direction.y * cos(rot_speed);
			double old_plane_x = player->plane.x;
			player->plane.x = player->plane.x * cos(rot_speed) - player->plane.y * sin(rot_speed);
			player->plane.y = old_plane_x * sin(rot_speed) + player->plane.y * cos(rot_speed);
		}
		render(renderer, maze, MAZE_WIDTH, MAZE_HEIGHT, tile_size, player); // Render the maze from the FPS perspective
	}
}
