#include "timer.h"

Uint32 start_time;
bool timer_active = true;
bool maze_completed = false;

void start_game() {
    start_time = SDL_GetTicks();  // Start the timer
    timer_active = true;
    maze_completed = false;
}

void update_timer_and_check_maze_completion(Player *player, int maze[MAZE_HEIGHT][MAZE_WIDTH], SDL_Renderer *renderer)
{
    (void)maze;

    if (!timer_active) return;

    Uint32 current_time = SDL_GetTicks();
    Uint32 elapsed_time = current_time - start_time;

    if (elapsed_time > 180000)
    {  /* 3 minutes = 180,000 milliseconds */
        timer_active = false;
        display_message("The Mayan Curse has got you!", renderer);
        return;
    }
    if (player->pos.x == MAZE_WIDTH - 2 && player->pos.y == MAZE_HEIGHT - 2)
    {
        maze_completed = true;
        display_message("You've Escaped the Mayan Wrath!", renderer);
        return;
    }
}

void display_message(const char *message, SDL_Renderer *renderer) {
    // Create a surface and texture for the message
    SDL_Surface* message_surface = TTF_RenderText_Solid(font, message, textColor);
    SDL_Texture* message_texture = SDL_CreateTextureFromSurface(renderer, message_surface);
    SDL_FreeSurface(message_surface);

    // Define the destination rectangle for the message
    SDL_Rect message_rect;
    message_rect.x = (WINDOW_WIDTH - message_surface->w) / 2;
    message_rect.y = (WINDOW_HEIGHT - message_surface->h) / 2;
    message_rect.w = message_surface->w;
    message_rect.h = message_surface->h;

    // Render the message
    SDL_RenderCopy(renderer, message_texture, NULL, &message_rect);
    SDL_DestroyTexture(message_texture);
}
