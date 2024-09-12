#ifndef INIT_H
#define INIT_H

#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int init_sdl(SDL_Window **window, SDL_Renderer **renderer);
int init_audio();
int init_ttf();
TTF_Font *load_font(const char *path, int size);
void cleanup(SDL_Renderer *renderer, SDL_Window *window);

extern SDL_Color textColor;
extern TTF_Font *font;

#endif /* INIT_H */
