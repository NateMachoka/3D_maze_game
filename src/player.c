#include <math.h>
#include "player.h"
#include "maze.h"
#include "config.h"
#include "player.h"
#include <math.h>

/**
 * degToRad - Convert degrees to radians
 * @deg:degrees to convert
 *
 * Return: the equivalent radians
 */
float degToRad(float deg)
{
	return (deg * M_PI / 180.0f);
}

/**
 * init_player - Initialize the player's position, size, and color
 * @player: Pointer to the Player structure to initialize
 * @x: X position of the player
 * @y: Y position of the player
 * @w: Width of the player
 * @h: Height of the player
 * @color: Color of the player
 * Return: nothing
 */
void init_player(Player *player, int x, int y, int w, int h, SDL_Color color)
{
	player->pos.x = x;
	player->pos.y = y;
	player->rect.w = w;
	player->rect.h = h;
	player->rect.x = x;
	player->rect.y = y;
	player->color = color;

	player->angle = 0; /* Start facing right */
	player->fov = 60;  /* Field of view in degrees */

	/* Player's initial direction vector */
	player->direction.x = 1;
	player->direction.y = 0;

	/* Player's initial view plane for raycasting */
	player->plane.x = 0;
	player->plane.y = 0.66f;
}

/**
 * update_player_direction_and_plane - Update the player's direction and plane based on angle
 * @player: Pointer to the Player structure
 * @angle: The new angle for the player
 * Return: none
 */
void update_player_direction_and_plane(Player *player, float angle)
{
	player->angle = angle;
	player->direction.x = cos(angle);
	player->direction.y = sin(angle);

	/* Update the view plane (perpendicular to direction) */
	player->plane.x = -sin(angle) * 0.66f;
	player->plane.y = cos(angle) * 0.66f;
}

/**
 * rotate_player - Rotate the player by a given angle (in radians)
 * @player: Pointer to the Player structure
 * @angle_change: Angle to rotate the player by (in radians)
 * Return: none
 */
void rotate_player(Player *player, float angle_change)
{
	player->angle += angle_change;

	/* Keep the angle in the range [0, 2π] */
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	if (player->angle >= 2 * M_PI)
		player->angle -= 2 * M_PI;

	update_player_direction_and_plane(player, player->angle);
}
/**
 * move_player - Moves the player to a new position with collision detection
 * @player: Pointer to the Player structure to be moved
 * @maze: The maze in which the player is moving
 * @tile_size: The size of each tile in the maze
 * Return: nothing
 */
void move_player(Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], int tile_size)
{
	int new_x, new_y;
	float move_x, move_y;
	float distance = player->speed;

	/* Calculate new position based on direction and distance */
	move_x = player->pos.x + player->direction.x * distance;
	move_y = player->pos.y + player->direction.y * distance;

	/* Calculate new grid coordinates */
	new_x = (int)(move_x / tile_size);
	new_y = (int)(move_y / tile_size);

	/* Check if the new position is within the maze */
	if (new_x >= 0 && new_x < MAZE_WIDTH && new_y >= 0 && new_y < MAZE_HEIGHT)
	{
		if (maze[new_y][new_x] == 0 || maze[new_y][new_x] == 2)
		{
			player->pos.x = move_x;
			player->pos.y = move_y;
			player->rect.x = (int)move_x;
			player->rect.y = (int)move_y;
		}
	}
}

/**
 * draw_player - Draw the player on the screen
 * @renderer: SDL_Renderer to draw on
 * @player: Pointer to the Player structure
 */
void draw_player(SDL_Renderer *renderer, const Player *player)
{
	SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
	SDL_Rect rect = { player->pos.x, player->pos.y, player->rect.w, player->rect.h };

	SDL_RenderFillRect(renderer, &rect);
}
