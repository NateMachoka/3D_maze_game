#include "maze.h"
#include <stdlib.h>
#include <time.h>

/**
 * directions - Array of possible directions to move in the maze.
 * Right, Down, Left, Up.
 */
const Point directions[4] =
{
    {0, 1},   // Right
    {1, 0},   // Down
    {0, -1},  // Left
    {-1, 0}   // Up
};

/**
 * in_bounds - Checks if a coordinate is within the maze boundaries.
 * @x: The x-coordinate to check.
 * @y: The y-coordinate to check.
 * @width: The width of the maze.
 * @height: The height of the maze.
 *
 * Returns: true if the coordinate is within bounds, false otherwise.
 */
bool in_bounds(int x, int y, int width, int height)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

/**
 * shuffle_directions - Randomly shuffles an array of directions.
 * @dirs: Pointer to the array of directions to shuffle.
 * @n: The number of directions in the array.
 */
void shuffle_directions(Point *dirs, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Point temp = dirs[i];
        dirs[i] = dirs[j];
        dirs[j] = temp;
    }
}

/**
 * carve_passages - Recursively carves passages in the maze using a depth-first search algorithm.
 * @maze: The 2D array representing the maze.
 * @x: The current x-coordinate in the maze.
 * @y: The current y-coordinate in the maze.
 * @width: The width of the maze.
 * @height: The height of the maze.
 */
void carve_passages(int maze[MAZE_HEIGHT][MAZE_WIDTH], int x, int y, int width, int height)
{
    Point shuffled_dirs[4];
    for (int i = 0; i < 4; i++)
    {
        shuffled_dirs[i] = directions[i];
    }
    shuffle_directions(shuffled_dirs, 4);

    for (int i = 0; i < 4; i++)
    {
        Point dir = shuffled_dirs[i];
        int nx = x + dir.x * 2;
        int ny = y + dir.y * 2;

        if (in_bounds(nx, ny, width, height) && maze[ny][nx] == 1)
        {
            maze[y + dir.y][x + dir.x] = 0; // Set the wall between the current and next point as PATH
            maze[ny][nx] = 0;
            carve_passages(maze, nx, ny, width, height);
        }
    }
}

/**
 * init_maze - Initializes the maze with walls and carves out passages.
 * @maze: The 2D array representing the maze to initialize.
 *
 * This function sets up the maze with walls around the edges, defines 
 * the entry point at (1, 1) and the exit point at (MAZE_HEIGHT - 2, MAZE_WIDTH - 2),
 * and then generates the maze using the carve_passages function starting from (1, 1).
 */
void init_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH])
{
    srand((unsigned int)time(NULL));

    // Initialize maze with walls
    for (int y = 0; y < MAZE_HEIGHT; ++y)
    {
        for (int x = 0; x < MAZE_WIDTH; ++x)
        {
            maze[y][x] = 1; // WALL
        }
    }

    // Define entry and exit points
    maze[1][1] = 0; // Entry point (top-left)
    maze[MAZE_HEIGHT - 2][MAZE_WIDTH - 2] = 0; // Exit point (bottom-right)

    // Generate the maze starting from (1, 1)
    carve_passages(maze, 1, 1, MAZE_WIDTH, MAZE_HEIGHT);
}
