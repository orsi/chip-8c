#ifndef OPCODES
#define OPCODES

// source: https://en.wikipedia.org/wiki/CHIP-8
// NNN: address
// NN: 8-bit constant
// N: 4-bit constant
// X and Y: 4-bit register identifier
// PC : Program Counter
// I : 16bit register (For memory address) (Similar to void pointer)
// VN: One of the 16 available variables. N may be 0 to F (hexadecimal)

void call();                            // 0NNN
void display_clear();                   // 00E0
void return_from_subroutine();          // 00EE
void jump_to();                         // 1NNN
void call_to();                         // 2NNN
void skip_if_vx_nn();                   // 3XNN
void skip_if_vx_not_nn();               // 4XNN
void skip_if_vx_vy();                   // 5XY0
void set_vx_to_nn();                    // 6XNN
void add_nn_to_vx();                    // 7XNN
void set_vx_to_vy();                    // 8XY0
void set_vx_to_vx_or_vy();              // 8XY1
void set_vx_to_vx_and_vy();             // 8XY2
void set_vx_to_vx_xor_vy();             // 8XY3
void add_vy_to_vx();                    // 8XY4
void subtract_vy_from_vx();             // 8XY5
void store_lobit_vf_shift_vx_right();   // 8XY6
void set_vx_to_vy_minus_vx();           // 8XY7
void store_hibit_vf_shift_vx_left();    // 8XYE
void skip_vx_not_equal_vy();            // 9XY0
void set_index_to();                    // ANNN
void jump_to_plus_v0();                 // BNNN
void set_vx_to_rand();                  // CXNN
void draw_at_vx_vy();                   // DXYN
void skip_vx_pressed();                 // EX9E
void skip_vx_not_pressed();             // EXA1
void set_vx_to_delay_timer();           // FX07
void await_and_store_vx();              // FX0A
void set_delay_timer_to_vx();           // FX15
void set_sound_timer_to_vx();           // FX18
void add_vx_to_index();                 // FX1E
void set_index_to_sprite_at_vx();       // FX29
void store_binary_dec_vx();             // FX33
void store_v0_vx_memory();              // FX55
void fill_v0_vx_memory();               // FX65
#endif