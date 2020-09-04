#ifndef UI
#define UI
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 1280

#include <SDL.h>
#include "chip8.h"

void setup_window(
    SDL_Window** window,
    SDL_Renderer** renderer,
    SDL_Texture** texture
);
void buffer_graphics(
    Chip8 *chip8,
    uint32_t *buffer,
    SDL_Renderer *renderer
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
