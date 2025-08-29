#include <stdio.h>
#include <stdlib.h>

#include "rom.h"
#include "gb.h"
#include "common.h"

int main(int argc, char *argv[]) {

    rom_context_t *rom = load_rom("./rom/tetris.gb");
    gb_state_t *gb = gb_init(rom);
    
    EMU_LOG("emulator initialized");
    gb_execute_cycle(gb);
    gb_execute_cycle(gb);
    gb_execute_cycle(gb);
    gb_execute_cycle(gb);


    free_rom(rom);
    free_gb(gb);

    return 0;
}