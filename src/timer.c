#include <SDL2/SDL_ttf.h>
#include "timer.h"
#include "main.h"

Uint32 start_time;
bool timer_active = true;
bool maze_completed = false;

/**
 * start_game - Initialize and start the game timer.
 *
 * Return: void
 */
void start_game()
{
	start_time = SDL_GetTicks();
	timer_active = true;
	maze_completed = false;
}

/**
 * update_timer_and_check_maze_completion - Update the timer and check if the maze is completed.
 * @player: Pointer to the Player structure containing the player's position
 * @maze: 2D array representing the maze.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 * @wall_texture: texture of the maze wall
 * @tile_size: size of each tile in the maze
 *
 * Return: 1 if the game should restart, 0 if it continues
 */
int update_timer_and_check_maze_completion(Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], SDL_Renderer *renderer, SDL_Texture *wall_texture, int tile_size)
{
	(void)maze;

	if (!timer_active)
		return (0);

	Uint32 current_time = SDL_GetTicks();
	Uint32 elapsed_time = current_time - start_time;

	if (elapsed_time > 150000)
	{ /* 2 and a half minutes = 150,000 milliseconds */
		timer_active = false;
		display_message("The Mayan Curse has got you!", renderer);
		SDL_Delay(3000);
		restart_game(renderer, player, maze, wall_texture, tile_size);
		return (1);
	}

	if (player->pos.x == END_X && player->pos.y == END_Y)
	{
		maze_completed = true;
		display_message("That Was Close!\n""You've Escaped the Mayan Wrath!", renderer);
		SDL_Delay(3000);
		restart_game(renderer, player, maze, wall_texture, tile_size);
		return (1);
	}
	return (0);
}

/**
 * display_message - Display a message on the screen.
 * @message: The message to be displayed.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 *
 * Return: void
 */
void display_message(const char *message, SDL_Renderer *renderer)
{
	/* Create a surface and texture for the message */
	SDL_Surface* message_surface = TTF_RenderText_Solid(font, message, textColor);
	if (!message_surface)
	{
		fprintf(stderr, "Error creating surface: %s\n", TTF_GetError());
		return;
	}
	SDL_Texture* message_texture = SDL_CreateTextureFromSurface(renderer, message_surface);
	SDL_FreeSurface(message_surface);
	 if (!message_texture)
	 {
		 fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
		 return;
	 }

	/* Define the destination rectangle for the message */
	SDL_Rect message_rect;
	message_rect.x = (WINDOW_WIDTH - message_surface->w) / 2;
	message_rect.y = (WINDOW_HEIGHT - message_surface->h) / 2;
	message_rect.w = message_surface->w;
	message_rect.h = message_surface->h;

	/* Clear the renderer */
	SDL_RenderClear(renderer);

	/* Render the message */
	SDL_RenderCopy(renderer, message_texture, NULL, &message_rect);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(message_texture);
}

/**
 * display_timer - Display the elapsed time since the start of the game.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 * @start_time: The start time of the game in milliseconds.
 *
 * Return: void
 */
void display_timer(SDL_Renderer *renderer, Uint32 start_time)
{
	Uint32 current_time = SDL_GetTicks();
	Uint32 elapsed_time = current_time - start_time;
	Uint32 remaining_time = 150000 - elapsed_time;

	if (remaining_time <= 0)
	{
		remaining_time = 0; /* Ensure remaining time doesn't go negative */
	}

	/* Convert remaining time to minutes and seconds */
	Uint32 minutes = remaining_time / 60000;
	Uint32 seconds = (remaining_time % 60000) / 1000;
	char time_text[20];
	snprintf(time_text, sizeof(time_text), "Time: %02u:%02u", minutes, seconds);

	/* Create a surface and texture for the timer */
	SDL_Surface* time_surface = TTF_RenderText_Solid(font, time_text, textColor);
	SDL_Texture* time_texture = SDL_CreateTextureFromSurface(renderer, time_surface);
	SDL_FreeSurface(time_surface);

	/* Define the destination rectangle for the timer */
	SDL_Rect time_rect;
	time_rect.x = 10; // Top-left corner with some padding
	time_rect.y = 10;
	time_rect.w = time_surface->w;
	time_rect.h = time_surface->h;

	/* Render the timer */
	SDL_RenderCopy(renderer, time_texture, NULL, &time_rect);
	SDL_DestroyTexture(time_texture);
}
