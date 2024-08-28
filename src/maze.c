#include "maze.h"
#include <stdlib.h>
#include <time.h>

/**
 * in_bounds - Checks if coordinates are within maze bounds.
 * @x: The x-coordinate.
 * @y: The y-coordinate.
 * 
 * Return: True if coordinates are within bounds, false otherwise.
 */
bool in_bounds(int x, int y) {
    return x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT;
}

/**
 * shuffle_directions - Randomly shuffles the directions for maze carving.
 * @dirs: Array of directions.
 * @n: Number of directions.
 */
void shuffle_directions(Point *dirs, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Point temp = dirs[i];
        dirs[i] = dirs[j];
        dirs[j] = temp;
    }
}

/**
 * carve_passages - Recursively carves passages in the maze using DFS.
 * @maze: 2D array representing the maze.
 * @x: The current x-coordinate.
 * @y: The current y-coordinate.
 */
void carve_passages(int maze[MAZE_HEIGHT][MAZE_WIDTH], int x, int y) {
    const Point directions[4] = {
        {0, 1},   // Right
        {1, 0},   // Down
        {0, -1},  // Left
        {-1, 0}   // Up
    };

    Point shuffled_dirs[4];
    for (int i = 0; i < 4; i++) {
        shuffled_dirs[i] = directions[i];
    }
    shuffle_directions(shuffled_dirs, 4);

    for (int i = 0; i < 4; i++) {
        Point dir = shuffled_dirs[i];
        int nx = x + dir.x * 2;
        int ny = y + dir.y * 2;

        if (in_bounds(nx, ny) && maze[ny][nx] == 1) {
            maze[y + dir.y][x + dir.x] = 0; // Carve passage
            maze[ny][nx] = 0; // Carve passage
            carve_passages(maze, nx, ny);
        }
    }
}

/**
 * generate_maze - Generates a maze with guaranteed connectivity between start and end points.
 * @maze: 2D array representing the maze.
 * 
 * The maze is initialized with walls and then passages are carved using DFS.
 * Ensures there is a path between the entry and exit points.
 */
void generate_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH]) {
    srand((unsigned int)time(NULL));

    // Initialize maze with walls
    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            maze[y][x] = 1; // 1 represents wall
        }
    }

    // Define entry and exit points
    int entry_x = 1;
    int entry_y = 1;
    int exit_x = MAZE_WIDTH - 2;
    int exit_y = MAZE_HEIGHT - 2;

    // Start carving from the entry point
    maze[entry_y][entry_x] = 0;
    carve_passages(maze, entry_x, entry_y);

    // Ensure there's a path from entry to exit
    if (!has_path(maze, entry_x, entry_y, exit_x, exit_y)) {
        generate_maze(maze); // Regenerate if no path found
    } else {
        maze[exit_y][exit_x] = 0; // Ensure exit is clear
    }
}

/**
 * has_path - Checks if there is a path between the start and end points using DFS.
 * @maze: 2D array representing the maze.
 * @start_x: The x-coordinate of the start point.
 * @start_y: The y-coordinate of the start point.
 * @end_x: The x-coordinate of the end point.
 * @end_y: The y-coordinate of the end point.
 * 
 * Return: True if a path exists, false otherwise.
 */
bool has_path(int maze[MAZE_HEIGHT][MAZE_WIDTH], int start_x, int start_y, int end_x, int end_y) {
    bool visited[MAZE_HEIGHT][MAZE_WIDTH] = { false };
    Point stack[MAZE_WIDTH * MAZE_HEIGHT];
    int top = -1;

    stack[++top] = (Point){ start_x, start_y };
    visited[start_y][start_x] = true;

    while (top >= 0) {
        Point current = stack[top--];
        int x = current.x;
        int y = current.y;

        if (x == end_x && y == end_y) {
            return true;
        }

        const Point directions[4] = {
            {0, 1},   // Right
            {1, 0},   // Down
            {0, -1},  // Left
            {-1, 0}   // Up
        };

        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i].x;
            int ny = y + directions[i].y;

            if (in_bounds(nx, ny) && !visited[ny][nx] && maze[ny][nx] == 0) {
                visited[ny][nx] = true;
                stack[++top] = (Point){ nx, ny };
            }
        }
    }

    return false;
}

/**
 * place_start_end - Places the entry and exit points and ensures there's a path between them.
 * @maze: 2D array representing the maze.
 * 
 * The entry point is placed at (1,1) and the exit point at (MAZE_WIDTH-2, MAZE_HEIGHT-2).
 * Ensures the maze has a valid path from entry to exit.
 */
void place_start_end(int maze[MAZE_HEIGHT][MAZE_WIDTH]) {
    int entry_x = 1;
    int entry_y = 1;
    int exit_x = MAZE_WIDTH - 2;
    int exit_y = MAZE_HEIGHT - 2;

    maze[entry_y][entry_x] = 0; // Entry point
    maze[exit_y][exit_x] = 0; // Exit point

    // Ensure the maze has a path from entry to exit
    if (!has_path(maze, entry_x, entry_y, exit_x, exit_y)) {
        generate_maze(maze); // Regenerate if no path exists
        place_start_end(maze);
    }
}
