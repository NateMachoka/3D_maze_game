#ifndef MAZE_H
#define MAZE_H

#include "config.h"
#include <stdbool.h>

#define WALL 1
#define PATH 0
#define START 2
#define END 3

extern int maze[MAZE_HEIGHT][MAZE_WIDTH];

bool in_bounds(int x, int y);
void shuffle_directions(int directions[4][2]);
void carve_passages(int x, int y, int maze[MAZE_HEIGHT][MAZE_WIDTH]) ;
void generate_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH]);
bool has_path(int maze[MAZE_HEIGHT][MAZE_WIDTH], int start_x, int start_y, int end_x, int end_y);
void place_start_end(int maze[MAZE_HEIGHT][MAZE_WIDTH]);

#endif // MAZE_H
