#include <SDL2/SDL.h>
#include "events.h"
#include "render.h"
#include "player.h"
#include "maze.h"
#include "config.h"

/**
 * handle_rotation - Handles player rotation based on key press
 * @player: Pointer to the Player structure
 * @state: Array representing the state of all keyboard keys
 *
 * Return: nothing
 */
void handle_rotation(Player *player, const Uint8 *state)
{
	if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A])
	{
		rotate_player(player, degToRad(-5));
	}

	if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])
	{
		rotate_player(player, degToRad(5));
	}
}

/**
 * handle_movement - Handles player movement based on key press
 * @player: Pointer to the Player structure
 * @state: Array representing the state of all keyboard keys
 * @maze: The maze in which the player is moving
 * @tile_size: The size of each tile in the maze
 *
 * Return: nothing
 */
void handle_movement(Player *player, const Uint8 *state, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size)
{
/* Initialize player speed */
	player->speed = 0.0f;

	if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
	{
		player->speed = 5.0f;
		move_player(player, maze, tile_size);
	}

	if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
	{
		player->speed = -5.0f;
		move_player(player, maze, tile_size);
	}
}

/**
 * event_loop - Main event loop handling player movement, rotation, and rendering
 * @renderer: SDL_Renderer used for rendering the maze and player
 * @player: Pointer to the Player structure
 * @maze: The maze in which the player is moving
 * @tile_size: The size of each tile in the maze
 *
 * Return: nothing
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

		/* Get the state of all keyboard keys */
		state = SDL_GetKeyboardState(NULL);

		handle_rotation(player, state);
		handle_movement(player, state, maze, tile_size);

		render(renderer, maze, TILE_SIZE, player);
	}
}
