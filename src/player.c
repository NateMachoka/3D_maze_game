#include "player.h"

/**
 * init_player - Initializes a Player structure
 * @player: Pointer to the Player structure to be initialized
 * @x: X position of the player
 * @y: Y position of the player
 * @width: Width of the player
 * @height: Height of the player
 * @color: Color of the player
 */

void init_player(Player *player, int x, int y, int w, int h, SDL_Color color)
{
	player->pos.x = x;
	player->pos.y = y;
	player->rect.x = x;
	player->rect.y = y;
	player->rect.w = w;
	player->rect.h = h;
	player->color = color;
}

/**
 * draw_player - Draws the player on the renderer
 * @renderer: Pointer to SDL_Renderer used for rendering
 * @player: Pointer to the Player structure to be drawn
 */
void draw_player(SDL_Renderer *renderer, const Player *player)
{
	SDL_SetRenderDrawColor(renderer, player->color.r, player->color.g, player->color.b, player->color.a);
	SDL_RenderFillRect(renderer, &player->rect);
}

/**
 * move_player - Moves the player to a new position
 * @player: Pointer to the Player structure to be moved
 * @x: New X position of the player
 * @y: New Y position of the player
 */

void move_player(Player *player, int x, int y)
{
	player->pos.x = x;
	player->pos.y = y;
	player->rect.x = x;
	player->rect.y = y;
}
