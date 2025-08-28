#include <stdint.h>
#include <stdlib.h>

#include "gb.h"

gb_state_t *gb_init() {
    gb_state_t *gb = (gb_state_t *) malloc(sizeof(gb_state_t));

    for(int i = 0; i < 0xFFFF; i++)
        gb->mem[i] = 0;

    // initial register state after DMG boot rom (possibly unimportant)
    gb->AF = 0x0100;
    gb->BC = 0x0013;
    gb->DE = 0x00D8;
    gb->HL = 0x014D;
    gb->SP = 0xFFFE;
    gb->PC = 0x100;  // skip boot rom (0-0FF) and begin cartridge rom execution

    return gb;
}

uint8_t gb_fetch_op(gb_state_t *gb) {
    return gb->mem[gb->PC];
}

void gb_execute_cycle(gb_state_t *gb) {
    switch(gb_fetch_op(gb)) {
        case 0xD3: case 0xE3: case 0xE4: case 0xF4: case 0xDB: case 0xEB:
        case 0xEC: case 0xFC: case 0xDD: case 0xED: case 0xFD:
        /* invalid opcodes */
        break;

        case 0x00: /* NOP */ break;
        case 0xCB: /* Prefixed */ break;
    }
}


void op_byte_ld(uint8_t n, uint8_t nn) {
}