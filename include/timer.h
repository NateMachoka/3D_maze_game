#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "config.h"
#include "player.h"
#include "maze.h"

void start_game();
void update_timer_and_check_maze_completion(Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], SDL_Renderer *renderer);
void display_message(const char *message, SDL_Renderer *renderer);

extern SDL_Renderer *renderer;
extern TTF_Font *font;
extern SDL_Color textColor;

#endif // TIMER_H
