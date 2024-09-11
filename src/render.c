#include "render.h"
#include <SDL2/SDL.h>
#include "maze.h"
#include "player.h"
#include "raycasting.h"

/**
 * is_walkable - Checks if a tile is walkable (not a wall).
 * @maze: The maze array.
 * @x: X position of the tile.
 * @y: Y position of the tile.
 * Return: 1 if walkable, 0 if not.
 */
int is_walkable(int maze[MAZE_HEIGHT][MAZE_WIDTH], int x, int y)
{
    if (x < 0 || x >= MAZE_WIDTH || y < 0 || y >= MAZE_HEIGHT)
        return 0;
    return maze[y][x] != 1; /* Assuming 1 is a wall */
}

/**
 * draw_maze - Draws the full maze on the screen.
 * @renderer: Pointer to SDL_Renderer used for rendering.
 * @maze: The 2D array representing the maze.
 * @tile_size: The size of each tile in the maze.
 * @start_x: X position of the start point.
 * @start_y: Y position of the start point.
 * @end_x: X position of the end point.
 * @end_y: Y position of the end point.
 */
void draw_maze(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size, int start_x, int start_y, int end_x, int end_y)
{
    int x, y;

    for (y = 0; y < MAZE_HEIGHT; ++y)
    {
        for (x = 0; x < MAZE_WIDTH; ++x)
        {
            SDL_Color color;
            SDL_Rect rect;

            /* Set default color for walkable tiles */
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;

            if (maze[y][x] == 1)  /* Wall */
            {
                color.r = 0;
                color.g = 0;
                color.b = 0;
                color.a = 255;
            }
            else if (x == start_x && y == start_y)  /* Start point */
            {
                color.r = 0;
                color.g = 255;
                color.b = 0;
                color.a = 255;
            }
            else if (x == end_x && y == end_y)  /* End point */
            {
                color.r = 255;
                color.g = 0;
                color.b = 0;
                color.a = 255;
            }
            else
            {
                /* Check surroundings to determine if it's a junction or corridor */
                int walkable_neighbors = 0;

                if (is_walkable(maze, x + 1, y)) walkable_neighbors++;
                if (is_walkable(maze, x - 1, y)) walkable_neighbors++;
                if (is_walkable(maze, x, y + 1)) walkable_neighbors++;
                if (is_walkable(maze, x, y - 1)) walkable_neighbors++;

                if (walkable_neighbors > 2)  /* Junction */
                {
                    color.r = 255;
                    color.g = 255;
                    color.b = 0;  /* Yellow for junction */
                    color.a = 255;
                }
                else if (walkable_neighbors == 2)  /* Corridor */
                {
                    color.r = 200;
                    color.g = 200;
                    color.b = 200;  /* Light gray for corridor */
                    color.a = 255;
                }
            }

            /* Draw the tile */
            rect.x = x * tile_size;
            rect.y = y * tile_size;
            rect.w = tile_size;
            rect.h = tile_size;

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect);
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

	for (y = 0; y < MAZE_HEIGHT; ++y)
	{
		for (x = 0; x < MAZE_WIDTH; ++x)
		{
			SDL_Color color;
			SDL_Rect rect;

			if (maze[y][x] == 1) /* wall */
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
 */
void render(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size, Player *player)
{
	int map_tile_size;
	int screen_width, screen_height, map_width, map_height;
	int map_x, map_y;

	/* Get screen dimensions */
	SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);

	clear_screen(renderer);

	/* Render the 3D view (main view) */
	cast_rays(renderer, player, maze, tile_size);

	/* Render the 2D map in the top-right corner */
	map_width = screen_width / 4;
	map_height = screen_height / 4;

	map_tile_size = (map_width < map_height ? map_width : map_height) / MAZE_WIDTH;

	map_x = screen_width - (map_width) - 10;
	map_y = 10;	/* Draw the 2D minimap */

	draw_map(renderer, maze, map_x, map_y, map_tile_size, player->pos.x / tile_size, player->pos.y / tile_size, player->angle);

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
