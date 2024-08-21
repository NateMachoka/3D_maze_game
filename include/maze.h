#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include "config.h"

#define MAZE_WIDTH 50
#define MAZE_HEIGHT 50
#define WALL_THICKNESS 2

// Directions for moving in the maze
typedef struct {
    int x, y;
} Point;

void init_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH]);

#endif // MAZE_H
