#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL.h>
#include "chip8.h"
#include "ui.h"

int main(int argc, char ** argv) {
    if (argv[1] == NULL) {
        printf("chip8c requires the filename as an argument: ./chip8c path/to/rom\n");
        exit(EXIT_FAILURE);
    }

    // setup chip8
    Chip8 chip8;
    init(&chip8);

    SDL_Window* chip8_window = NULL;
    SDL_Renderer* chip8_renderer = NULL;
    SDL_Texture* chip8_texture = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    setup_window(&chip8_window, &chip8_renderer, &chip8_texture);

    int division_cycles = 0;
    int total_cycles = 0;
    uint32_t *pixel_buffer = malloc((SCREEN_WIDTH * SCREEN_HEIGHT) * sizeof(uint32_t));

    load_rom(&chip8, argv[1]);

    while(chip8.is_running_flag) {
        execute_opcode(&chip8);
        division_cycles++;
        total_cycles++;

        // If the draw screen flag was set to true during the last 
        // instruction, render the updated screen and then clear the flag
        if (chip8.draw_screen_flag) {
            buffer_graphics(&chip8, pixel_buffer, chip8_renderer);
            draw_graphics(pixel_buffer, chip8_renderer, chip8_texture);
            chip8.draw_screen_flag = false;
        }
        
        do {
            process_user_input(&chip8);
        } while (chip8.is_paused_flag && chip8.is_running_flag);

        if (division_cycles == 9) {
            update_timers(&chip8);
            division_cycles = 0;
        }

        usleep(1000);
    }

    // close window and free data
    close_window(chip8_window, chip8_renderer, chip8_texture);
    free(pixel_buffer);
    return 0;
}
