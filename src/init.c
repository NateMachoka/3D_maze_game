#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "timer.h"
#include "init.h"
#include <stdio.h>

SDL_Color textColor;
TTF_Font *font = NULL;

/**
 * init_sdl - Initializes SDL and creates the window and renderer
 * @window: Pointer to SDL_Window pointer to be initialized
 * @renderer: Pointer to SDL_Renderer pointer to be initialized
 *
 * Return: 0 on success, 1 on error
 */
int init_sdl(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow(
        "The Maze",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (*window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    *renderer = SDL_CreateRenderer(
        *window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (*renderer == NULL)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 1;
    }

    return 0;
}

/**
 * init_audio - Initializes SDL_mixer for audio
 *
 * Return: 0 on success, 1 on error
 */
int init_audio()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }
    return 0;
}

/**
 * init_ttf - Initializes SDL_ttf for font rendering
 *
 * Return: 0 on success, 1 on error
 */
int init_ttf()
{
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }
    return 0;
}

/**
 * load_font - Loads a font from file
 * @path: Path to the font file
 * @size: Size of the font
 *
 * Return: Pointer to the loaded font, or NULL if failed
 */
TTF_Font *load_font(const char *path, int size)
{
    TTF_Font *font = TTF_OpenFont(path, size);
    if (font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    return font;
}

