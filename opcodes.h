#ifndef OPCODES
#define OPCODES

#include "chip8.h"

// source: https://en.wikipedia.org/wiki/CHIP-8
// NNN: address
// NN: 8-bit constant
// N: 4-bit constant
// X and Y: 4-bit register identifier
// PC : Program Counter
// I : 16bit register (For memory address) (Similar to void pointer)
// VN: One of the 16 available variables. N may be 0 to F (hexadecimal)

void call(Chip8 *chip8);                            // 0NNN
void display_clear(Chip8 *chip8);                   // 00E0
void return_from_subroutine(Chip8 *chip8);          // 00EE
void jump_to(Chip8 *chip8);                         // 1NNN
void call_to(Chip8 *chip8);                         // 2NNN
void skip_if_vx_nn(Chip8 *chip8);                   // 3XNN
void skip_if_vx_not_nn(Chip8 *chip8);               // 4XNN
void skip_if_vx_vy(Chip8 *chip8);                   // 5XY0
void set_vx_to_nn(Chip8 *chip8);                    // 6XNN
void add_nn_to_vx(Chip8 *chip8);                    // 7XNN
void set_vx_to_vy(Chip8 *chip8);                    // 8XY0
void set_vx_to_vx_or_vy(Chip8 *chip8);              // 8XY1
void set_vx_to_vx_and_vy(Chip8 *chip8);             // 8XY2
void set_vx_to_vx_xor_vy(Chip8 *chip8);             // 8XY3
void add_vy_to_vx(Chip8 *chip8);                    // 8XY4
void subtract_vy_from_vx(Chip8 *chip8);             // 8XY5
void store_lobit_vf_shift_vx_right(Chip8 *chip8);   // 8XY6
void set_vx_to_vy_minus_vx(Chip8 *chip8);           // 8XY7
void store_hibit_vf_shift_vx_left(Chip8 *chip8);    // 8XYE
void skip_vx_not_equal_vy(Chip8 *chip8);            // 9XY0
void set_index_to(Chip8 *chip8);                    // ANNN
void jump_to_plus_v0(Chip8 *chip8);                 // BNNN
void set_vx_to_rand(Chip8 *chip8);                  // CXNN
void draw_at_vx_vy(Chip8 *chip8);                   // DXYN
void skip_vx_pressed(Chip8 *chip8);                 // EX9E
void skip_vx_not_pressed(Chip8 *chip8);             // EXA1
void set_vx_to_delay_timer(Chip8 *chip8);           // FX07
void await_and_store_vx(Chip8 *chip8);              // FX0A
void set_delay_timer_to_vx(Chip8 *chip8);           // FX15
void set_sound_timer_to_vx(Chip8 *chip8);           // FX18
void add_vx_to_index(Chip8 *chip8);                 // FX1E
void set_index_to_sprite_at_vx(Chip8 *chip8);       // FX29
void store_binary_dec_vx(Chip8 *chip8);             // FX33
void store_v0_vx_memory(Chip8 *chip8);              // FX55
void fill_v0_vx_memory(Chip8 *chip8);               // FX65
#endif