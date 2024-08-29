#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

/**
 * play_sound - Loads and plays a sound file
 * @file: Path to the sound file
 */
void play_sound(const char *file)
{
    Mix_Chunk *sound = Mix_LoadWAV(file);
    if (!sound)
    {
        SDL_Log("Failed to load sound: %s, SDL_mixer Error: %s", file, Mix_GetError());
        return;
    }

    if (Mix_PlayChannel(-1, sound, 0) == -1)
    {
        SDL_Log("Failed to play sound: %s, SDL_mixer Error: %s", file, Mix_GetError());
    }

    SDL_Delay(500);
    Mix_FreeChunk(sound);
}
