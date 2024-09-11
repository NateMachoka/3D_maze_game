#include "player.h"
#include "maze.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

/**
 * cast_rays - Casts rays from the player 's position and renders the 3D view
 * @renderer: The SDL renderer to draw with.
 * @player: The player's information (position, direction, etc.).
 * @maze: The 2D array representing the maze.
 * @tile_size: The size of each tile in the maze.
 */
void cast_rays(SDL_Renderer *renderer, Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size, SDL_Texture *wall_texture)
{
    int x, hit, side, lineHeight, drawStart, drawEnd;
    int mapX, mapY, stepX, stepY;
    float cameraX, rayDirX, rayDirY, sideDistX, sideDistY, perpWallDist;
    float deltaDistX, deltaDistY;

    int textureWidth = 1024;  // Texture width in pixels
    int textureHeight = 1024; // Texture height in pixels

    for (x = 0; x < WINDOW_WIDTH; x++) {
        cameraX = 2 * x / (float)WINDOW_WIDTH - 1;
        rayDirX = player->direction.x + player->plane.x * cameraX;
        rayDirY = player->direction.y + player->plane.y * cameraX;

        mapX = (int)(player->pos.x / tile_size);
        mapY = (int)(player->pos.y / tile_size);

        hit = 0;

        // Calculate delta distances
        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        // Determine step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player->pos.x / tile_size - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->pos.x / tile_size) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player->pos.y / tile_size - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->pos.y / tile_size) * deltaDistY;
        }

        // Perform DDA (Digital Differential Analyzer) to find the wall
        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (maze[mapY][mapX] > 0) hit = 1; // Wall hit
        }

        // Calculate perpendicular wall distance
        if (side == 0) {
            perpWallDist = (mapX - player->pos.x / tile_size + (1 - stepX) / 2) / rayDirX;
        } else {
            perpWallDist = (mapY - player->pos.y / tile_size + (1 - stepY) / 2) / rayDirY;
        }

        // Calculate height of the wall slice to draw
        lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

        // Calculate the top and bottom of the line
        drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;

        drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawEnd >= WINDOW_HEIGHT) drawEnd = WINDOW_HEIGHT - 1;

        // Calculate where the wall was hit, to get the correct texture offset
        float wallX;
        if (side == 0) {
            wallX = player->pos.y / tile_size + perpWallDist * rayDirY;
        } else {
            wallX = player->pos.x / tile_size + perpWallDist * rayDirX;
        }
        wallX -= floor(wallX);  // Ensure value is between 0 and 1

        // x-coordinate on the texture
        int texX = (int)(wallX * (float)textureWidth);
        if (side == 0 && rayDirX > 0) texX = textureWidth - texX - 1;
        if (side == 1 && rayDirY < 0) texX = textureWidth - texX - 1;

        // Now render the vertical strip from the texture corresponding to the wall slice
        SDL_Rect srcRect = { texX, 0, 1, textureHeight };  // Source rectangle from the texture
        SDL_Rect destRect = { x, drawStart, 1, drawEnd - drawStart };  // Destination rectangle on the screen

        SDL_RenderCopy(renderer, wall_texture, &srcRect, &destRect);
    }
}
