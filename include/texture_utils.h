#ifndef TEXTURE_UTILS_H
#define TEXTURE_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file_path);

#endif /* TEXTURE_UTILS_H */
