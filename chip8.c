#include "chip8.h"

void load_rom(Chip8 *chip8, const char* file);
void init(Chip8 *chip8);
void reset(Chip8 chip8);
void get_opcode(Chip8 chip8);
void execute_opcode(Chip8 *chip8);
void process_user_input(Chip8 *chip8);
void update_timers(Chip8 *chip8);