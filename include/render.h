#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "player.h"
#include "maze.h"

void render(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size, Player *player);
void render_maze(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH]);
void clear_screen(SDL_Renderer *renderer);
void draw_maze(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int maze_width, int maze_height, int tile_size);

#endif // RENDER_H
