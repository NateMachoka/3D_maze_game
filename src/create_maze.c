#include <stdio.h>
#include <stdlib.h>

int** create_maze(int height, int width) {
    int **maze = malloc(height * sizeof(int *));
    if (maze == NULL) {
        perror("Failed to allocate memory for maze rows");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < height; i++) {
        maze[i] = malloc(width * sizeof(int));
        if (maze[i] == NULL) {
            perror("Failed to allocate memory for maze columns");
            exit(EXIT_FAILURE);
        }
    }

    return maze;
}

void free_maze(int **maze, int height) {
    for (int i = 0; i < height; i++) {
        free(maze[i]);
    }
    free(maze);
}
