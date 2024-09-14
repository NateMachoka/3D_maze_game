#ifndef MAIN_H
#define MAIN_H

#include "init.h"
#include "events.h"
#include "render.h"
#include "cleanup.h"
#include "player.h"

void restart_game(SDL_Renderer *renderer, Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], SDL_Texture *wall_texture, const int tile_size);

#endif /* MAIN_H */
