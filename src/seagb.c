#include <stdio.h>
#include <stdlib.h>

#include "rom.h"
#include "gb.h"

int main(int argc, char *argv[]) {

    rom_context_t *rom_ctx = load_rom("./rom/tetris.gb");

    gb_state_t *gb = gb_init();

    free_rom(rom_ctx);

    return 0;
}