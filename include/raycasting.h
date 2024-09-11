#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#include "player.h"
#include "maze.h"
#include "config.h"

void cast_rays(SDL_Renderer *renderer, Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size, SDL_Texture *wall_texture);

#endif /* RAYCASTING_H */
