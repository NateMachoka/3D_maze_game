#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "config.h"
#include "init.h"
#include "cleanup.h"
#include "events.h"
#include "render.h"
#include "maze.h"
#include "player.h"
#include "sound.h"
#include "raycasting.h"
#include "texture_utils.h"
#include "timer.h"

/**
 * restart_game - Reset the game state and restart the timer.
 * @player: Pointer to the Player structure to reset the player's position.
 * @maze: 2D array representing the maze.
 * @wall_texture: texture to be used for the walls
 * @tile_size: the size of each tile in the maze
 * Return: void
 */
void restart_game(SDL_Renderer *renderer, Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], SDL_Texture *wall_texture, const int tile_size)
{
	(void)renderer;
	(void)wall_texture;
	(void)tile_size;

	/* Generate a new maze and place start/end points */
	generate_maze(maze);
	place_start_end(maze);

	/* Reset player position and other states */
	SDL_Color player_color = {255, 0, 255, 255};
	init_player(player, tile_size, tile_size, tile_size, tile_size, player_color);

	/* Start the game timer */
	start_game();
}

/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	const int tile_size = TILE_SIZE;
	int maze[MAZE_HEIGHT][MAZE_WIDTH];
	int result;

	if (init_sdl(&window, &renderer) != 0)
	{
		return (1);
	}

	/* Initialize SDL_ttf and load font */
	if (init_ttf() != 0)
	{
		cleanup(renderer, window);
		return (1);
	}
	font = load_font("assets/Surabanglus.ttf", 40);
	if (font == NULL)
	{
		cleanup(renderer, window);
		return (1);
	}
	textColor = (SDL_Color){255, 255, 255, 255}; /* White color */

	/* Initialize SDL_mixer for audio */
	if (init_audio() != 0)
	{
		cleanup(renderer, window);
		return (1);
	}

	/* Load textures */
	SDL_Texture *wall_texture = load_texture(renderer, "assets/Mayan_wall");
	if (wall_texture == NULL)
	{
		fprintf(stderr, "Error loading wall texture\n");
		cleanup(renderer, window);
		return (1);
	}

	/* Initialize player */
	Player player;

	/* Game loop */
	bool quit = false;
	while (!quit)
	{/* Start or restart the game */
		restart_game(renderer, &player, maze, wall_texture, tile_size);

		/*Run the event loop for the current game round */
		result = event_loop(renderer, &player, maze, tile_size, wall_texture);

		/* Check if the player quit the game */
		if (result == 1)
		{
			quit = true;
		}
        /* If result == 0, the game will restart automatically */
	}

	/*Clean up resources before exiting */
	SDL_DestroyTexture(wall_texture);
	cleanup(renderer, window);

	return (0);
}
