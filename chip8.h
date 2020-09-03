#ifndef CHIP8
#define CHIP8

typedef struct {
    unsigned char memory[4096];
    unsigned short stack[16];

    // registers
    unsigned char registers[16];
    unsigned short program_counter;
    unsigned short index;
    unsigned short stack_pointer;

    // timers
    unsigned char delay_timer;
    unsigned char sound_timer;

    // display
    unsigned char graphics[64 * 32];

    // keys
    unsigned char keyboard[16];

    unsigned short current_opcode;
} Chip8;

void load_rom(Chip8 *chip8, const char* file);
#endif