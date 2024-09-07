#ifndef MAZE_H
#define MAZE_H

#include "config.h"

#define WALL 1
#define PATH 0
#define START 2
#define END 3

extern int maze[MAZE_HEIGHT][MAZE_WIDTH];

int (*get_maze())[MAZE_WIDTH];
void generate_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH]);
void place_start_end(int maze[MAZE_HEIGHT][MAZE_WIDTH]);

#endif // MAZE_H
