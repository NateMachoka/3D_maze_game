#include "player.h"
#include "maze.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

/**
 * cast_rays - Casts rays from the player's position and renders the 3D view
 * @renderer: The SDL renderer to draw with.
 * @player: The player's information (position, direction, etc.).
 * @maze: The 2D array representing the maze.
 * @tile_size: The size of each tile in the maze.
 */
void cast_rays(SDL_Renderer *renderer, Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size)
{
	int x, hit, side, lineHeight, drawStart, drawEnd;
	int mapX, mapY, stepX, stepY;
	float cameraX, rayDirX, rayDirY, sideDistX, sideDistY, perpWallDist;
	float deltaDistX, deltaDistY;

	for (x = 0; x < WINDOW_WIDTH; x++)
	{
		cameraX = 2 * x / (float)WINDOW_WIDTH - 1;
		rayDirX = player->direction.x + player->plane.x * cameraX;
		rayDirY = player->direction.y + player->plane.y * cameraX;

		mapX = (int)(player->pos.x / tile_size);
		mapY = (int)(player->pos.y / tile_size);

		hit = 0;
		/* Check for zero direction values */
		if (fabs(rayDirX) < 1e-6)
		{
			deltaDistX = 1e30; /* large no to avoid division by zero */
		}
		else
		{
			deltaDistX = fabs(1 / rayDirX);
		}
		if (fabs(rayDirY) < 1e-6)
		{
			deltaDistY = 1e30;
		}
		else
		{
			deltaDistY = fabs(1 / rayDirY);
		}

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->pos.x / tile_size - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->pos.x / tile_size) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->pos.y / tile_size - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->pos.y / tile_size) * deltaDistY;
		}

		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (maze[mapY][mapX] > 0) hit = 1;
		}

		if (side == 0)
		{
			perpWallDist = (mapX - player->pos.x / tile_size + (1 - stepX) / 2) / rayDirX;
		}
		else
		{
			perpWallDist = (mapY - player->pos.y / tile_size + (1 - stepY) / 2) / rayDirY;
		}
		lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

		drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;

		if (drawStart < 0)
			drawStart = 0;

		drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;

		if (drawEnd >= WINDOW_HEIGHT)
			drawEnd = WINDOW_HEIGHT - 1;

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
	}
}
