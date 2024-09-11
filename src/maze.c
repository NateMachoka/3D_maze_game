#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maze.h"

/**
 * in_bounds - Check if a position is within the maze boundaries.
 * @x: x-coordinate of the position.
 * @y: y-coordinate of the position.
 *
 * Return: true if the position is within bounds, false otherwise.
 */
bool in_bounds(int x, int y)
{
	return (x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT);
}

/**
 * shuffle_directions - Shuffle an array of directions randomly.
 * @directions: 2D array representing four directions (down, right, up, left).
 *
 * Return: void.
 */
void shuffle_directions(int directions[4][2])
{
	int i, j;
	int temp[2];

	for (i = 0; i < 4; i++)
	{
		j = i + rand() / (RAND_MAX / (4 - i) + 1);
		temp[0] = directions[i][0];
		temp[1] = directions[i][1];
		directions[i][0] = directions[j][0];
		directions[i][1] = directions[j][1];
		directions[j][0] = temp[0];
		directions[j][1] = temp[1];
	}
}

/**
 * carve_passages - Recursively carve passages in the maze using DFS.
 * @x: x-coordinate of the current cell.
 * @y: y-coordinate of the current cell.
 * @maze: 2D array representing the maze (walls and paths).
 *
 * Return: void.
 */
void carve_passages(int x, int y, int maze[MAZE_HEIGHT][MAZE_WIDTH])
{
	int i;
	int dx, dy, nx, ny;

	static const int directions[4][2] = {
		{ 0, 2 },  /* Down */
		{ 2, 0 },  /* Right */
		{ 0, -2 }, /* Up */
		{ -2, 0 }  /* Left */
	};
	int shuffled_directions[4][2];

	memcpy(shuffled_directions, directions, sizeof(directions));
	shuffle_directions(shuffled_directions);

	maze[y][x] = PATH;

	for (i = 0; i < 4; i++)
	{
		dx = shuffled_directions[i][0];
		dy = shuffled_directions[i][1];
		nx = x + dx;
		ny = y + dy;

		if (in_bounds(nx, ny) && maze[ny][nx] == WALL)
		{
			maze[ny - dy / 2][nx - dx / 2] = PATH; /* Carve through wall */
			carve_passages(nx, ny, maze);
		}
	}
}

/**
 * generate_maze - Generate a maze using the DFS algorithm.
 * @maze: 2D array representing the maze to be filled.
 *
 * Return: void.
 */
void generate_maze(int maze[MAZE_HEIGHT][MAZE_WIDTH])
{
	int x, y;
	int start_x, start_y;

	/* Initialize the maze with walls */
	for (y = 0; y < MAZE_HEIGHT; y++)
	{
		for (x = 0; x < MAZE_WIDTH; x++)
		{
			maze[y][x] = WALL;
		}
	}

	/* Start carving passages from a random position */
	srand(time(NULL));  /* Seed the random number generator */
	start_x = 1 + (rand() % (MAZE_WIDTH / 2)) * 2;
	start_y = 1 + (rand() % (MAZE_HEIGHT / 2)) * 2;
	carve_passages(start_x, start_y, maze);
}

/**
 * has_path - Check if there is a path between two points in the maze using BFS.
 * @maze: 2D array representing the maze (walls and paths).
 * @start_x: x-coordinate of the start point.
 * @start_y: y-coordinate of the start point.
 * @end_x: x-coordinate of the end point.
 * @end_y: y-coordinate of the end point.
 *
 * Return: true if there is a path, false otherwise.
 */
bool has_path(int maze[MAZE_HEIGHT][MAZE_WIDTH], int start_x, int start_y, int end_x, int end_y)
{
	int i, nx, ny, x, y;
	int queue[MAZE_WIDTH * MAZE_HEIGHT][2];
	int front = 0, back = 0;

	const int directions[4][2] = {
		{ 1, 0 },  /* Right */
		{ 0, 1 },  /* Down */
		{ -1, 0 }, /* Left */
		{ 0, -1 }  /* Up */
	};
	bool visited[MAZE_HEIGHT][MAZE_WIDTH];

	if (!in_bounds(start_x, start_y) || !in_bounds(end_x, end_y) ||
        maze[start_y][start_x] == WALL || maze[end_y][end_x] == WALL)
	{
		return (false);
	}

	/* BFS setup */
	memset(visited, false, sizeof(visited));
	queue[back][0] = start_x;
	queue[back][1] = start_y;
	back++;
	visited[start_y][start_x] = true;

	while (front < back)
	{
		x = queue[front][0];
		y = queue[front][1];
		front++;

		/* Check if we have reached the end */
		if (x == end_x && y == end_y)
		{
			return (true);
		}

		/* Explore neighbors */
		for (i = 0; i < 4; i++)
		{
			nx = x + directions[i][0];
			ny = y + directions[i][1];

			if (in_bounds(nx, ny) && !visited[ny][nx] && maze[ny][nx] != WALL)
			{
				queue[back][0] = nx;
				queue[back][1] = ny;
				back++;
				visited[ny][nx] = true;
			}
		}
	}
	return (false);
}

/**
 * place_start_end - Place the start and end points in the maze.
 * @maze: 2D array representing the maze.
 *
 * Return: void.
 */
void place_start_end(int maze[MAZE_HEIGHT][MAZE_WIDTH])
{
	maze[1][1] = START;
	maze[MAZE_HEIGHT-2][MAZE_WIDTH-2] = END;
}
