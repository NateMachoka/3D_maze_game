#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#include "player.h"
#include "maze.h"
#include "config.h"

void cast_rays(SDL_Renderer *renderer, const Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size);

#endif /* RAYCASTING_H */
