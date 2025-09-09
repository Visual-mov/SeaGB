#ifndef PPU_H
#define PPU_H

#include "common.h"

typedef struct ppu_tile_t {
    u8 data[64]; // color indicies

} ppu_tile_t;

typedef struct ppu_state_t {
    u8 vram[0x1FFF];

} ppu_state_t;


#endif