#include "render.h"
#include <SDL2/SDL.h>
#include "maze.h"
#include "player.h"
#include "raycasting.h"

/**
 * draw_maze - Draws the full maze on the screen using textures.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 * @maze: The 2D array representing the maze.
 * @tile_size: The size of each tile in the maze.
 * @start_x: X position of the start point.
 * @start_y: Y position of the start point.
 * @end_x: X position of the end point.
 * @end_y: Y position of the end point.
 * @wall_texture: The texture to use for drawing walls.
 */
void draw_maze(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size, int start_x, int start_y, int end_x, int end_y, SDL_Texture *wall_texture)
{
	int x, y;
	SDL_Rect srcRect = {0, 0, tile_size, tile_size}; /* Source rectangle for the texture */
	SDL_Rect destRect; /* Destination rectangle for rendering */

	for (y = 0; y < MAZE_HEIGHT; ++y)
	{
		for (x = 0; x < MAZE_WIDTH; ++x)
		{
			destRect.x = x * tile_size;
			destRect.y = y * tile_size;
			destRect.w = tile_size;
			destRect.h = tile_size;

			if (maze[y][x] == 1) // Wall
			{
				SDL_RenderCopy(renderer, wall_texture, &srcRect, &destRect);
			}
			else if (x == start_x && y == start_y) /* Start point */
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderFillRect(renderer, &destRect);
			}
			else if (x == end_x && y == end_y) // End point
			{
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderFillRect(renderer, &destRect);
			}
		}
	}
}

/**
 * draw_map - Draws the 2D map on the renderer.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 * @maze: The 2D array representing the maze.
 * @map_x: X position of the map on the screen.
 * @map_y: Y position of the map on the screen.
 * @map_tile_size: The size of each tile on the map.
 * @player_x: Player's X position in the maze.
 * @player_y: Player's Y position in the maze.
 */
void draw_map(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int map_x, int map_y, int map_tile_size, int player_x, int player_y, float player_angle)
{
	int x, y;
	SDL_Color color;
	SDL_Rect rect;

	for (y = 0; y < MAZE_HEIGHT; ++y)
	{
		for (x = 0; x < MAZE_WIDTH; ++x)
		{
			if (maze[y][x] == 1) /* Wall */
			{
				color.r = 0;
				color.g = 0;
				color.b = 0;
				color.a = 255;
			}
			else
			{
				color.r = 255;
				color.g = 255;
				color.b = 255;
				color.a = 255;
			}
			rect.x = map_x + (x * map_tile_size);
			rect.y = map_y + (y * map_tile_size);
			rect.w = map_tile_size;
			rect.h = map_tile_size;

			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	/* Draw the player on the map */
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect player_rect = {
		.x = map_x + (player_x * map_tile_size),
		.y = map_y + (player_y * map_tile_size),
		.w = map_tile_size,
		.h = map_tile_size
	};
	SDL_RenderFillRect(renderer, &player_rect);

	/* Draw the player's direction */
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(
		renderer,
		map_x + (player_x * map_tile_size) + map_tile_size / 2,
		map_y + (player_y * map_tile_size) + map_tile_size / 2,
		map_x + (player_x * map_tile_size) + map_tile_size / 2 + cos(player_angle) * map_tile_size / 2,
		map_y + (player_y * map_tile_size) + map_tile_size / 2 + sin(player_angle) * map_tile_size / 2
		);
}

/**
 * render - Renders the current state of the maze and the 2D map.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 * @maze: The 2D array representing the maze.
 * @tile_size: The size of each tile in the full maze.
 * @player: The player's information (position, direction, etc.).
 * @wall_texture: The texture to use for drawing walls.
 */
void render(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size, Player *player, SDL_Texture *wall_texture)
{
	int map_tile_size;
	int screen_width, screen_height, map_width, map_height;
	int map_x, map_y;

	/* Get screen dimensions */
	SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);
	clear_screen(renderer);

	/* Render the 3D view (main view) */
	cast_rays(renderer, player, maze, tile_size, wall_texture);

	/* Render the 2D map in the top-right corner */
	map_width = screen_width / 4;
	map_height = screen_height / 4;

	map_tile_size = (map_width < map_height ? map_width : map_height) / MAZE_WIDTH;

	map_x = screen_width - (map_width) - 10;
	map_y = 10; /* Draw the 2D minimap */

	draw_map(renderer, maze, map_x, map_y, map_tile_size, player->pos.x / tile_size, player->pos.y / tile_size, player->angle);
	display_timer(renderer, start_time);

	SDL_RenderPresent(renderer);
}

/**
 * clear_screen - Clears the screen with a given color.
 * @renderer: The SDL renderer to draw with.
 */
void clear_screen(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
