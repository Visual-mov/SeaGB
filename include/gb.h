#ifndef GB_H
#define GB_H

#include <stdint.h>
#include "common.h"
#include "rom.h"

typedef struct gb_state_t {
    u8 mem[0xFFFF];

    // CPU
    u16 AF;         // accumulator and flags regs
    u16 BC, DE, HL; // general purpose 16-bit regs
    u16 SP, PC;     // stack-pointer, program-counter 
    bool fz, fn, fh, fc; // zero, subtraction, half-carry and carry flags


} gb_state_t;

gb_state_t *gb_init(rom_context_t *rom);
void free_gb(gb_state_t *gb);

void gb_update(gb_state_t *gb);
void gb_execute_cycle(gb_state_t *gb);


#endif