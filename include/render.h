#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "player.h"
#include "raycasting.h"
#include "maze.h"
#include "timer.h"

void draw_maze(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size, int start_x, int start_y, int end_x, int end_y, SDL_Texture *wall_texture);
void draw_map(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int map_x, int map_y, int map_tile_size, int player_x, int player_y, float player_angle);
void render(SDL_Renderer *renderer, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size, Player *player, SDL_Texture *wall_texture);
void clear_screen(SDL_Renderer *renderer);

#endif // RENDER_H
