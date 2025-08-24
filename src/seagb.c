#include <stdio.h>
#include <stdlib.h>

#include "rom.h"

int main(int argc, char *argv[]) {

    rom_context_t *rom_ctx = load_rom("./rom/linksawakening_dx.gbc");
    //rom_context_t *rom_ctx = load_rom("./rom/tetris.gb");
    free_rom(rom_ctx);

    return 0;
}