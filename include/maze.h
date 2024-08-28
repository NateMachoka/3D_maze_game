#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include "config.h"



// Directions for moving in the maze
typedef struct {
    int x, y;
} Point;

void init_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH]);

#endif // MAZE_H
