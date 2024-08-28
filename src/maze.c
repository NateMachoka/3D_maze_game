#include "config.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "maze.h"

/**
 * directions - Array of possible movement directions in the maze
 */
const Point directions[4] =
{
	{0, 1},   // Right
	{1, 0},   // Down
	{0, -1},  // Left
	{-1, 0}   // Up
};

/**
 * in_bounds - Checks if a point is within the bounds of the maze
 * @x: The x-coordinate to check
 * @y: The y-coordinate to check
 * @width: The width of the maze
 * @height: The height of the maze
 *
 * Return: true if the point is within bounds, false otherwise
 */
bool in_bounds(int x, int y, int width, int height)
{
	return x >= 0 && x < width && y >= 0 && y < height;
}

/**
 * shuffle_directions - Randomly shuffles an array of directions
 * @dirs: The array of directions to shuffle
 * @n: The number of directions in the array
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
 * generate_maze - Recursively generates the maze using a depth-first search algorithm
 * @maze: The 2D array representing the maze
 * @x: The current x-coordinate
 * @y: The current y-coordinate
 * @width: The width of the maze
 * @height: The height of the maze
 */
void generate_maze(int maze[][MAZE_WIDTH], int x, int y, int width, int height)
{
	maze[y][x] = 0;

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
			generate_maze(maze, nx, ny, width, height);
		}
	}
}

/**
 * init_maze - Initializes the maze with a random maze generation algorithm
 * @maze: The 2D array representing the maze to initialize
 *
 * Initializes the maze with walls and generates a path using the depth-first search algorithm.
 * Ensures that the start and end points are clear.
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
// Generate the maze starting from (1, 1)
	generate_maze(maze, 1, 1, MAZE_WIDTH, MAZE_HEIGHT);
// Ensure the start and end points are clear
	maze[1][1] = 0; // PATH
	maze[MAZE_HEIGHT - 2][MAZE_WIDTH - 2] = 0; // PATH
}
