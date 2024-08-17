#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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

	SDL_Window *window;
	SDL_Renderer *renderer;
	int running = 1;
	SDL_Event event;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return (1);
	}
	window = SDL_CreateWindow(
		"3D Maze Game",                 /* Window title */
		SDL_WINDOWPOS_CENTERED,         /* Initial x position */
		SDL_WINDOWPOS_CENTERED,         /* Initial y position */
		WINDOW_WIDTH, WINDOW_HEIGHT,    /* Width and height in pixels */
		SDL_WINDOW_SHOWN                /* Flags */
		);
	if (window == NULL)
	{
		printf("SDL_CreateWindow: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = 0;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
