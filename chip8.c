#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"

// loads rom file into memory starting at 0x200
void load_rom(Chip8 *chip8, const char* file) {
    long rom_length;
    uint8_t *rom_buffer;

    FILE *rom = fopen(file, "rb");
    if (rom != NULL) {
        // get size of rom to allocate memory for buffer
        fseek(rom, 0, SEEK_END);
        rom_length = ftell(rom);
        rewind(rom);
        rom_buffer = (uint8_t*) malloc(sizeof(uint8_t) * rom_length);
        if (rom_buffer == NULL) {
            printf("Allocation error\n");
            exit(EXIT_FAILURE);
        }

        // read rom into memory
        fread(rom_buffer, sizeof(uint8_t), rom_length, rom);

        // check size of rom
        if ((0xFFF - 0x200) >= rom_length) {
            printf("Data \n");
            for (int i = 0; i < rom_length; i++) {
                chip8->RAM[i + 0x200] = rom_buffer[i];
                printf("%x", rom_buffer[i]);
            }
        } else {
            printf("Rom is too large.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(rom);
    free(rom_buffer);
}

// Initialize the default state
void init(Chip8 *chip8) {
    chip8->program_counter = 0;
    chip8->current_opcode = 0;
    chip8->stack_pointer = 0;
    chip8->index = 0;

    // clear display
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        chip8->graphics[i] = 0;
    }

    // clear stack
    for (int i = 0; i < STACK_SIZE; i++) {
        chip8->stack[i] = 0;
    }

    // clear ram
    for (int i = 0; i < MAX_MEMORY; i++) {
        chip8->RAM[i] = 0;
    }

    // clear registers
    for (int i = 0; i < NUM_REGISTERS; i++) {
        chip8->V[i] = 0;
    }

    // load fonts into memory
    for (int i = 0; i < FONT_SIZE; i++) {
        chip8->RAM[i] = font_set[i];
    }

    // reset timers
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;

    // keyboard
    for (int i = 0; i < NUM_KEYS; i++) {
        chip8->keyboard[i] = 0;
    }
}

// similar to init but keeps ram
void reset(Chip8 *chip8) {
    chip8->program_counter = 0;
    chip8->current_opcode = 0;
    chip8->stack_pointer = 0;
    chip8->index = 0;

    // clear display
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        chip8->graphics[i] = 0;
    }

    // clear stack
    for (int i = 0; i < STACK_SIZE; i++) {
        chip8->stack[i] = 0;
    }

    // clear ram from fontset end to program start
    for (int i = FONT_SIZE; i < ROM_START; i++) {
        chip8->RAM[i] = 0;
    }

    // clear registers
    for (int i = 0; i < NUM_REGISTERS; i++) {
        chip8->V[i] = 0;
    }

    // keyboard
    for (int i = 0; i < NUM_KEYS; i++) {
        chip8->keyboard[i] = 0;
    }

    // reset timers
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
}
void get_opcode(Chip8 chip8);
void execute_opcode(Chip8 *chip8);
void process_user_input(Chip8 *chip8);
void update_timers(Chip8 *chip8);