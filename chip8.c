#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"

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
                chip8->memory[i + 0x200] = rom_buffer[i];
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
void init(Chip8 *chip8);
void reset(Chip8 chip8);
void get_opcode(Chip8 chip8);
void execute_opcode(Chip8 *chip8);
void process_user_input(Chip8 *chip8);
void update_timers(Chip8 *chip8);