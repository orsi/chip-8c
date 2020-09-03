#include <stdint.h>
#include "chip8.h"

// 0NNN
void call(Chip8 *chip8) {}
// 00E0
void display_clear(Chip8 *chip8) {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        chip8->graphics[i] = 0;
    }
    chip8->program_counter += 2;
}
// 00EE
void return_from_subroutine(Chip8 *chip8) {
    chip8->stack_pointer--;
    chip8->program_counter = chip8->stack[chip8->stack_pointer];
    chip8->program_counter += 2;
}
// 1NNN
void jump_to(Chip8 *chip8) {
    uint16_t address = chip8->current_opcode & 0x0FFF;
    chip8->program_counter = address;
}
// 2NNN
void call_to(Chip8 *chip8) {
    uint16_t address = chip8->current_opcode & 0xFFF;
    chip8->stack[chip8->stack_pointer] = chip8->program_counter;
    chip8->stack_pointer++;
    chip8->program_counter = address;
}
// 3XNN
void skip_if_vx_nn(Chip8 *chip8) {
    uint8_t v_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t value = chip8->current_opcode & 0x00FF;
    if (chip8->V[v_index] == value) {
        chip8->program_counter += 4;
    } else {
        chip8->program_counter += 2;
    }
}
// 4XNN
void skip_if_vx_not_nn(Chip8 *chip8) {
    uint8_t v_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t value = chip8->current_opcode & 0x00FF;
    if (chip8->V[v_index] != value) {
        chip8->program_counter += 4;
    } else {
        chip8->program_counter += 2;
    }
}
// 5XY0
void skip_if_vx_vy(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    if (chip8->V[vx_index] == chip8->V[vy_index]) {
        chip8->program_counter += 4;
    } else {
        chip8->program_counter += 2;
    }
}
// 6XNN
void set_vx_to_nn(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->current_opcode & 0x00FF;
    chip8->V[vx_index] = nn;
    chip8->program_counter += 2;
}
// 7XNN
void add_nn_to_vx(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->current_opcode & 0x00FF;
    chip8->V[vx_index] += nn;
    chip8->program_counter += 2;
}
// 8XY0
void set_vx_to_vy(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    chip8->V[vx_index] = chip8->V[vy_index];
    chip8->program_counter += 2;
}
// 8XY1
void set_vx_to_vx_or_vy(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    chip8->V[vx_index] = chip8->V[vx_index] | chip8->V[vy_index];
    chip8->program_counter += 2;
}
// 8XY2
void set_vx_to_vx_and_vy(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    chip8->V[vx_index] = chip8->V[vx_index] & chip8->V[vy_index];
    chip8->program_counter += 2;
}
// 8XY3
void set_vx_to_vx_xor_vy(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    chip8->V[vx_index] = chip8->V[vx_index] ^ chip8->V[vy_index];
    chip8->program_counter += 2;
}
// 8XY4
void add_vy_to_vx(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    chip8->V[vx_index] += chip8->V[vy_index];
    chip8->program_counter += 2;
}
// 8XY5
void subtract_vy_from_vx(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    chip8->V[vx_index] -= chip8->V[vy_index];
    chip8->program_counter += 2;
}
// 8XY6
void store_lobit_vf_shift_vx_right(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    chip8->V[0xF] = chip8->V[vx_index] & 00000001;
    chip8->V[vx_index] = chip8->V[vx_index] >> 1;
    chip8->program_counter += 2;
}
// 8XY7
void set_vx_to_vy_minus_vx(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    if (chip8->V[vx_index] < chip8->V[vy_index]) {
        chip8->V[0xF] = 0;
    } else {
        chip8->V[0xF] = 1;
    }
    chip8->V[vx_index] = chip8->V[vx_index] - chip8->V[vy_index];
    chip8->program_counter += 2;
}
// 8XYE
void store_hibit_vf_shift_vx_left(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    chip8->V[0xF] = chip8->V[vx_index] & 10000000;
    chip8->V[vx_index] = chip8->V[vx_index] << 1;
    chip8->program_counter += 2;
}
// 9XY0
void skip_vx_not_equal_vy(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    if (chip8->V[vx_index] != chip8->V[vy_index]) {
        chip8->program_counter += 4;
    } else {
        chip8->program_counter += 2;
    }
}
// ANNN
void set_index_to(Chip8 *chip8) {
    uint16_t value = chip8->current_opcode & 0x0FFF;
    chip8->index = value;
    chip8->program_counter += 2;
}
// BNNN
void jump_to_plus_v0(Chip8 *chip8) {
    uint16_t nnn = chip8->current_opcode & 0x0FFF;
    chip8->program_counter = chip8->V[0] + nnn;
}
// CXNN
void set_vx_to_rand(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t nn = chip8->current_opcode & 0x00FF;
    chip8->V[vx_index] = (rand() % 256) & nn;
    chip8->program_counter += 2;
}
// DXYN
void draw_at_vx_vy(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    uint8_t vy_index = (chip8->current_opcode & 0x00F0) >> 4;
    uint8_t n = chip8->current_opcode & 0x000F;

    // draw 8 x n pixels at V[X], V[Y]
    // TODO

    // set V[F] = 1 if any pixel flipped, else V[F] = 0
    chip8->program_counter += 2;
}
// EX9E
void skip_vx_pressed(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    // if (chip8->keyboard[] == chip8->V[vx_index]) {
    //     chip8->program_counter += 4;
    // } else {
    //     chip8->program_counter += 2;
    // }
}
// EXA1
void skip_vx_not_pressed(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    // if (chip8->keyboard[] != chip8->V[vx_index]) {
    //     chip8->program_counter += 4;
    // } else {
    //     chip8->program_counter += 2;
    // }
}
// FX07
void set_vx_to_delay_timer(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    chip8->V[vx_index] = chip8->delay_timer;
    chip8->program_counter += 2;
}
// FX0A
void await_and_store_vx(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    // chip8->V[vx_index] = get_keypressed();
    chip8->program_counter += 2;
}
// FX15
void set_delay_timer_to_vx(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    chip8->delay_timer = chip8->V[vx_index];
    chip8->program_counter += 2;
}
// FX18
void set_sound_timer_to_vx(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    chip8->sound_timer = chip8->V[vx_index];
    chip8->program_counter += 2;
}
// FX1E
void add_vx_to_index(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    chip8->index += chip8->V[vx_index];
    chip8->program_counter += 2;
}
// FX29
void set_index_to_sprite_at_vx(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    chip8->index += chip8->RAM[chip8->V[vx_index]];
    chip8->program_counter += 2;
}
// FX33
void store_binary_dec_vx(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    chip8->RAM[chip8->index] = chip8->V[vx_index] & 0x0F00;
    chip8->RAM[chip8->index + 1] = chip8->V[vx_index] & 0x00F0;
    chip8->RAM[chip8->index + 2] = chip8->V[vx_index] & 0x000F;
    chip8->program_counter += 2;
}
// FX55
void store_v0_vx_memory(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    for (int i = 0; i < vx_index; i++) {
        chip8->RAM[chip8->index + i] = chip8->V[i];
    }
    chip8->program_counter += 2;
}
// FX65
void fill_v0_vx_memory(Chip8 *chip8) {
    uint8_t vx_index = (chip8->current_opcode & 0x0F00) >> 8;
    for (int i = 0; i < vx_index; i++) {
        chip8->V[i] = chip8->RAM[chip8->index + i];
    }
    chip8->program_counter += 2;
}