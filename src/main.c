#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <SDL.h>
#include "chip8.h"
#include "ui.h"
#include "audio.h"

int main(int argc, char ** argv) {
    if (argv[1] == NULL) {
        printf("chip8c requires the filename as an argument: ./chip8c path/to/rom\n");
        exit(EXIT_FAILURE);
    }

    // setup chip8
    Chip8 chip8;
    init(&chip8);

    // setup graphics window
    SDL_Window* chip8_window = NULL;
    SDL_Renderer* chip8_renderer = NULL;
    SDL_Texture* chip8_texture = NULL;
    SDL_Init(SDL_INIT_EVERYTHING);
    setup_window(&chip8_window, &chip8_renderer, &chip8_texture);

    // setup audio
    setup_audio();

    // load rom
    load_rom(&chip8, argv[1]);

    // setup timers and graphics buffer
    int cpuHz = 500; // hz
    int timerAccumulator = 0;
    int timerHz = 60; //hz
    int timerCpuCycles = 500 / 60;
    int usecDelay = 1000 * 1000 / cpuHz;
    uint32_t *pixel_buffer = malloc((SCREEN_WIDTH * SCREEN_HEIGHT) * sizeof(uint32_t));

    // emulator loop
    while(chip8.is_running_flag) {
        timerAccumulator++;

        execute_opcode(&chip8);

        if (chip8.draw_screen_flag) {
            buffer_graphics(&chip8, pixel_buffer, chip8_renderer);
            draw_graphics(pixel_buffer, chip8_renderer, chip8_texture);
            chip8.draw_screen_flag = false;
        }
        
        do {
            process_user_input(&chip8);
        } while (chip8.is_paused_flag && chip8.is_running_flag);

        // timers update at 60hz
        if (timerAccumulator > timerCpuCycles) {
            update_timers(&chip8);
            if (chip8.sound_timer > 0) {
                play_tone();
            } else {
                stop_audio();
            }
            timerAccumulator = 0;
        }

        usleep(usecDelay);
    }

    // close window and free data
    close_window(chip8_window, chip8_renderer, chip8_texture);
    free(pixel_buffer);
    return 0;
}
