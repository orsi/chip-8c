#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"
#include "opcodes.h"

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
    } else {
        printf("Could not open file from %s.\n", file);
        exit(EXIT_FAILURE);
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
    for (int y = 0; y <  SCREEN_HEIGHT; y++) {
        for (int x = 0; x <  SCREEN_WIDTH; x++) {
            chip8->graphics[x][y] = 0;
        }
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

    // keyboard
    for (int i = 0; i < NUM_KEYS; i++) {
        chip8->keyboard[i] = 0;
    }

    // reset timers
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
}

// similar to init but keeps ram
void reset(Chip8 *chip8) {
    chip8->program_counter = 0;
    chip8->current_opcode = 0;
    chip8->stack_pointer = 0;
    chip8->index = 0;

    // clear display
    for (int y = 0; y <  SCREEN_HEIGHT; y++) {
        for (int x = 0; x <  SCREEN_WIDTH; x++) {
            chip8->graphics[x][y] = 0;
        }
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
uint16_t next_opcode(Chip8 *chip8) {
    uint16_t opcode;
    uint8_t most_significant_bit = chip8->RAM[chip8->program_counter];
    uint8_t least_significant_bit = chip8->RAM[chip8->program_counter + 1];
    opcode = most_significant_bit << 8 | least_significant_bit;
    chip8->current_opcode = opcode;
    return opcode;
}
// executes the current opcode
void execute_opcode(Chip8 *chip8) {
    uint16_t opcode = next_opcode(chip8);

    switch(opcode & 0xF000) {
        case 0x0000:
            switch(opcode & 0x00FF) {
                case 0x00E0:
                    display_clear(chip8);
                    break;
                case 0x00EE:
                    return_from_subroutine(chip8);
                    break;
                default:
                    // call machine code?
                    break;
            }
            break;
        case 0x1000:
            jump_to(chip8);
            break;
        case 0x2000:
            call_to(chip8);
            break;
        case 0x3000:
            skip_if_vx_nn(chip8);                 
            break;
        case 0x4000:
            skip_if_vx_not_nn(chip8);             
            break;
        case 0x5000:
            skip_if_vx_vy(chip8);                 
            break;
        case 0x6000:
            set_vx_to_nn(chip8);                  
            break;
        case 0x7000:
            add_nn_to_vx(chip8);                  
            break;
        case 0x8000:
            switch(opcode & 0x000F) {
                case 0x0000:
                    set_vx_to_vy(chip8);                  
                    break;
                case 0x0001:
                    set_vx_to_vx_or_vy(chip8);            
                    break;
                case 0x0002:
                    set_vx_to_vx_and_vy(chip8);           
                    break;
                case 0x0003:
                    set_vx_to_vx_xor_vy(chip8);           
                    break;
                case 0x0004:
                    add_vy_to_vx(chip8);                  
                    break;
                case 0x0005:
                    subtract_vy_from_vx(chip8);           
                    break;
                case 0x0006:
                    store_lobit_vf_shift_vx_right(chip8); 
                    break;
                case 0x0007:
                    set_vx_to_vy_minus_vx(chip8);         
                    break;
                case 0x000E:
                    store_hibit_vf_shift_vx_left(chip8);  
                    break;
            }
            break;
        case 0x9000:
            skip_vx_not_equal_vy(chip8);          
            break;
        case 0xA000:
            set_index_to(chip8);                  
            break;
        case 0xB000:
            jump_to_plus_v0(chip8);               
            break;
        case 0xC000:
            set_vx_to_rand(chip8);                
            break;
        case 0xD000:
            draw_at_vx_vy(chip8);                 
            break;
        case 0xE000:
            switch(opcode & 0x00FF) {
                case 0x009E:
                    skip_vx_pressed(chip8);               
                    break;
                case 0x00A1:
                    skip_vx_not_pressed(chip8);           
                    break;
            }
            break;
        case 0xF000:
            switch(opcode & 0x00FF) {
                case 0x0007:
                    set_vx_to_delay_timer(chip8);         
                    break;
                case 0x000A:
                    await_and_store_vx(chip8);            
                    break;
                case 0x0015:
                    set_delay_timer_to_vx(chip8);         
                    break;
                case 0x0018:
                    set_sound_timer_to_vx(chip8);         
                    break;
                case 0x001E:
                    add_vx_to_index(chip8);               
                    break;
                case 0x0029:
                    set_index_to_sprite_at_vx(chip8);     
                    break;
                case 0x0033:
                    store_binary_dec_vx(chip8);           
                    break;
                case 0x0055:
                    store_v0_vx_memory(chip8);            
                    break;
                case 0x0065:
                    fill_v0_vx_memory(chip8);             
                    break;
            }
            break;
    }
}
void process_user_input(Chip8 *chip8);
void update_timers(Chip8 *chip8);