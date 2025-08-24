#ifndef GB_H
#define GB_H

#include <stdint.h>

typedef struct gb_state_t {
    cpu_state_t *cpu;
} gb_state_t;

typedef struct cpu_state_t {
    uint16_t SP, PC;    // stack-pointer, program-counter 
    uint8_t A, C, D, E, H, L;   // registers
    uint8_t F;      // flag register
} cpu_state_t;

#endif