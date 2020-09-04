#include <stdlib.h>
#include "chip8.h"
#include "lib/SDL2/SDL.h"
#include "ui.h"

int main(int argc, char ** argv) {
    if (argv[1] == NULL) {
        prinf("chip8c requires the filename as an argument: ./chip8c path/to/rom\n");
        exit(EXIT_FAILURE);
    }

    Chip8 chip8;
    SDL_Window* chip8_window = NULL;
    SDL_Renderer* chip8_renderer = NULL;
    SDL_Texture* chip8_texture = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);

    int division_cycles = 0;
    int total_cycles = 0;

    uint32_t *pixel_buffer = malloc((SCREEN_WIDTH * SCREEN_HEIGHT) * sizeof(uint32_t));

    setup_window(&chip8_window, &chip8_renderer, &chip8_texture);
    load_rom(&chip8, argv[1]);
    return 0;
}