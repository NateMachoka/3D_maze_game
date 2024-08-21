#include <SDL2/SDL.h>
#include "maze.h"

/**
 * init_maze - Initializes the maze with predefined values
 * @maze: Pointer to the 2D array representing the maze
 */
void init_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH])
{
	int x, y;

	int temp_maze[MAZE_HEIGHT][MAZE_WIDTH] =
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
			{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
			{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
			{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
			{1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
			{1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};
	for (y = 0; y < MAZE_HEIGHT; ++y)
	{
		for (x = 0; x < MAZE_WIDTH; ++x)
		{
			maze[y][x] = temp_maze[y][x];
		}
	}
}

/**
 * draw_maze - Draws the maze on the renderer
 * @renderer: Pointer to SDL_Renderer used for rendering
 * @maze: The maze representation
 * @maze_width: Width of the maze
 * @maze_height: Height of the maze
 * @tile_size: Size of each tile
 */
void draw_maze(SDL_Renderer *renderer, int maze[][MAZE_WIDTH], int maze_width, int maze_height, int tile_size)
{
	int x, y;

	for (y = 0; y < maze_height; y++)
	{
		for (x = 0; x < maze_width; x++)
		{
			if (maze[y][x] == 1)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // walll color is black
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //path color white
			}
			SDL_Rect tile = {x * tile_size, y * tile_size, tile_size, tile_size};
			SDL_RenderFillRect(renderer, &tile);
		}
	}
}
