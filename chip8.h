#ifndef CHIP8
#define CHIP8

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define STACK_SIZE 16
#define MAX_MEMORY 4096
#define NUM_REGISTERS 16
#define FONT_SIZE 64
#define NUM_KEYS 16
#define ROM_START 0x200
#define ROM_END 0xFFF
#define SPRITE_WIDTH 8

#include<SDL.h>

typedef struct {
    uint8_t RAM[MAX_MEMORY];
    uint16_t stack[STACK_SIZE];

    // registers
    uint8_t V[NUM_REGISTERS];
    uint16_t program_counter;
    uint16_t index;
    uint16_t stack_pointer;

    // timers
    uint8_t delay_timer;
    uint8_t sound_timer;

    // display
    uint8_t graphics[SCREEN_WIDTH][SCREEN_HEIGHT];

    // keys
    uint8_t keyboard[NUM_KEYS];

    uint16_t current_opcode;

    // status flags
    uint8_t is_running_flag;
    uint8_t draw_screen_flag;
    uint8_t is_paused_flag;
} Chip8;

const static uint8_t font_set[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80, // F
};

const static uint8_t KEYMAP[NUM_KEYS] = {
    SDLK_x, // 0
    SDLK_1, // 1
    SDLK_2, // 2
    SDLK_3, // 3
    SDLK_q, // 4
    SDLK_w, // 5
    SDLK_e, // 6
    SDLK_a, // 7
    SDLK_s, // 8
    SDLK_d, // 9
    SDLK_z, // A
    SDLK_c, // B
    SDLK_4, // C
    SDLK_r, // D
    SDLK_f, // E
    SDLK_v  // F
};

void load_rom(Chip8 *chip8, const char* file);
void init(Chip8 *chip8);
void reset(Chip8 *chip8);
uint16_t next_opcode(Chip8 *chip8);
void execute_opcode(Chip8 *chip8);
void process_user_input(Chip8 *chip8);
void update_timers(Chip8 *chip8);
#endif
