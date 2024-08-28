#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "player.h"
#include "maze.h"

void draw_maze(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size);
void render(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size, Player *player);
void clear_screen(SDL_Renderer *renderer);
#endif // RENDER_H
