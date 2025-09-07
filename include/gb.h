#ifndef GB_H
#define GB_H

#include <stdint.h>
#include "common.h"
#include "rom.h"

typedef struct gb_state_t {
    // CPU
    uint16_t AF;         // accumulator and flags regs
    uint16_t BC, DE, HL; // general purpose 16-bit regs
    uint16_t SP, PC;     // stack-pointer, program-counter 

    uint8_t mem[0xFFFF];
    uint8_t fz, fn, fh, fc; // zero, subtraction, half-carry and carry flags

} gb_state_t;

gb_state_t *gb_init(rom_context_t *rom);
void free_gb(gb_state_t *gb);

void gb_update(gb_state_t *gb);
void gb_execute_cycle(gb_state_t *gb);


#endif