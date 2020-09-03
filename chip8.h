// Chip-8 data structures and core runtime
unsigned char registers[16];
unsigned char memory[4096];
unsigned short opcode;
unsigned short index;
unsigned short program_counter;
unsigned char delay_timer;
unsigned char sound_timer;
unsigned char graphics[64 * 32];
unsigned char keyboard[16];
unsigned short stack[16];
unsigned short stack_pointer;