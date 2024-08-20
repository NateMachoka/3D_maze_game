#include <SDL2/SDL.h>
#include "main.h"

/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	if (init_sdl() != 0)
        return (1);

	event_loop();
	cleanup();

	return (0);
}
