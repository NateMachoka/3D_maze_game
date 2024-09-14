#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "config.h"
#include "player.h"
#include "maze.h"
#include "init.h"
#include "main.h"

void start_game();
int update_timer_and_check_maze_completion(Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], SDL_Renderer *renderer, SDL_Texture *wall_texture, int tile_size);
void display_message(const char *message, SDL_Renderer *renderer);
void display_timer(SDL_Renderer *renderer, Uint32 start_time);

extern SDL_Renderer *renderer;
extern Uint32 start_time;

#endif // TIMER_H
