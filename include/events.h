#ifndef EVENTS_H
#define EVENTS_H

#include "player.h"
#include "maze.h"

void event_loop(SDL_Renderer *renderer, Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size);

#endif /* EVENTS_H */
