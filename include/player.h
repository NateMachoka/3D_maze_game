#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "config.h"
/**
 * Position - Represents a 2D position in the game world.
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct {
    int x; // X coordinate
    int y; // Y coordinate
} Position;

/**
 * Player - Represents a player in the game
 * @pos: Position of the player
 * @rect: SDL_Rect structure representing the player's position and size
 * @color: SDL_Color structure representing the player's color
 * @direction: player's direction vector
 * @plane: camera plane for 3D rendering
 */

typedef struct {
	Position pos;
	SDL_Rect rect; // position and size of player
	SDL_Color color;
	SDL_Point direction;
	SDL_Point plane;
}Player;

void init_player(Player *player, int x, int y, int w, int h, SDL_Color color);
void draw_player(SDL_Renderer *renderer, const Player *player);
void move_player(Player *player, int x, int y, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size);


#endif //PLAYER_H
