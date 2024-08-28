#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>
#include "config.h"



// Directions for moving in the maze
typedef struct {
    int x, y;
} Point;

// Function prototypes
void generate_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH]);
void place_start_end(int maze[MAZE_HEIGHT][MAZE_WIDTH]);
bool has_path(int maze[MAZE_HEIGHT][MAZE_WIDTH], int start_x, int start_y, int end_x, int end_y);

#endif // MAZE_H
