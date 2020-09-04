#ifndef UI
#define UI
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 1280

#include "lib/SDL2/SDL.h"

void setup_window(
    SDL_Window** window,
    SDL_Renderer** renderer,
    SDL_Texture** texture
);
void buffer_graphics(
    uint32_t *buffer, 
    SDL_Renderer *renderer,
    SDL_Texture *texture
);
void draw_graphics(
    uint32_t *buffer,
    SDL_Renderer *renderer,
    SDL_Texture *texture
);
void close_window(
    SDL_Window *window,
    SDL_Renderer *renderer,
    SDL_Texture *texture
);
#endif