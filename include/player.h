#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "config.h"

/**
 * Vec2 - Represents a 2D vector with floating-point coordinates.
 * @x: The x-coordinate of the vector.
 * @y: The y-coordinate of the vector.
 */
typedef struct {
	float x;
	float y;
} Vec2;

/**
 * Player - Represents a player in the game.
 * @pos: The current position of the player in the game world.
 * @color: The color of the player used for rendering.
 * @direction: The direction the player is facing, used for movement and raycasting.
 * @plane: The 2D vector defining the player's view plane for raycasting.
 * @angle: The current angle of the player's orientation, in radians, used for rotating the view.
 */
typedef struct {
	Vec2 pos;
	SDL_Color color;
	SDL_Rect rect;
	Vec2 direction;
	Vec2 plane;
	float angle;
	float fov;
	float max_distance;
	float speed;
}Player;

float degToRad(float deg);
void init_player(Player *player, int x, int y, int w, int h, SDL_Color color);
void update_player_direction_and_plane(Player *player, float angle);
void draw_player(SDL_Renderer *renderer, const Player *player);
void rotate_player(Player *player, float angle_change);
void move_player(Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size);

#endif //PLAYER_H
