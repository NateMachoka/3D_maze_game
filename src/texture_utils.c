#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

 /**
 * load_texture - Load an image file and create an SDL texture from it.
 * @renderer: The SDL renderer used to create the texture.
 * @file_path: The file path to the image file to be loaded.
 *
 * Return: pointer to the created SDL texture, or
 * NULL if texture wasn't created
 */

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file_path)
{
	SDL_Surface *surface = IMG_Load(file_path); /* Load image from file path */

	if (!surface)
	{
		printf("IMG_Load Error: %s\n", IMG_GetError());
		return (NULL);
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	if (!texture)
	{
		printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
	}
	else
	{
		/* set texture filtering mode for sharpness or smooth scaling */
		SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
	}
	return (texture);
}
