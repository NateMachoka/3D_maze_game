#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>

// Define the maze dimensions
#define MAZE_WIDTH 10
#define MAZE_HEIGHT 10

extern int maze[MAZE_HEIGHT][MAZE_WIDTH];

void init_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH]);
void draw_maze(SDL_Renderer *renderer, int maze[][MAZE_WIDTH], int maze_width, int maze_height, int tile_size);


#endif // MAZE_H
