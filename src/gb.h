#ifndef GB_H
#define GB_H

#include <stdint.h>

typedef struct gb_state_t {
    // CPU
    uint16_t AF;         // accumulator and flags
    uint16_t BC, DE, HL; // general purpose 16-bit regs
    uint16_t SP, PC;     // stack-pointer, program-counter 

    uint8_t mem[0xFFFF];

} gb_state_t;

#endif