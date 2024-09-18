#include <stdio.h>
#include <stdlib.h>


/**
 * create_maze - Dynamically allocates memory for a 2D maze of given dimensions.
 * @height: The number of rows in the maze.
 * @width: The number of columns in the maze.
 *
 * Return: A pointer to the allocated 2D array representing the maze.
 */
int** create_maze(int height, int width)
{
	int ** maze;
	int i;

	maze = malloc(height * sizeof(int *));

	if (maze == NULL)
	{
		perror("Failed to allocate memory for maze rows");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < height; i++)
	{
		maze[i] = malloc(width * sizeof(int));

			if (maze[i] == NULL)
			{
				perror("Failed to allocate memory for maze columns");
				exit(EXIT_FAILURE);
			}
	}
	return maze;
}

/**
 * free_maze - Frees the dynamically allocated memory for the 2D maze.
 * @maze: The 2D array representing the maze.
 * @height: The number of rows in the maze.
 *
 * Return: void.
 */
void free_maze(int **maze, int height)
{
	int i;

	for (i = 0; i < height; i++)
	{
		free(maze[i]);
	}
	free(maze);
}
