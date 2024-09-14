#ifndef EVENTS_H
#define EVENTS_H

#include "player.h"
#include "maze.h"
#include "timer.h"

void handle_rotation(Player *player, const Uint8 *state);
void handle_movement(Player *player, const Uint8 *state, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size);
int event_loop(SDL_Renderer *renderer, Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size, SDL_Texture *wall_texture);

#endif /* EVENTS_H */
