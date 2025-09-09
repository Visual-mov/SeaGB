#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "gb.h"
#include "rom.h"
#include "common.h"

gb_state_t *gb_init(rom_context_t *rom) {
    gb_state_t *gb = (gb_state_t *) malloc(sizeof(gb_state_t));

    memset(gb->mem, 0x00, 0xFFFF); // zero out memory
    memcpy(gb->mem, rom->rom, 0x3FFF); // Copy rom bank 0
    memcpy(gb->mem + 0x4000, rom->rom + 0x4000, 0x3FFF); // Copy rom bank n

    // initial register state after DMG boot rom (possibly unimportant)
    gb->AF = 0x0100;
    gb->BC = 0x0013;
    gb->DE = 0x00D8;
    gb->HL = 0x014D;
    gb->SP = 0xFFFE;
    gb->PC = 0x0100;  // boot rom would end at 0FF. begin cartridge rom execution

    return gb;
}

void free_gb(gb_state_t *gb) {
    if(!gb)
        return;
    free(gb);
}

// Reads a byte from memory and advances the program counter
uint8_t gb_read_n(gb_state_t *gb) {
    return gb->mem[gb->PC++];
}
uint16_t gb_read_nn(gb_state_t *gb) {
    // convert to big endian
    uint8_t lsb = gb_read_n(gb);
    return gb_read_n(gb) << 8 | lsb;
}

void gb_execute_cycle(gb_state_t *gb) {
    uint16_t op_addr = gb->PC;
    uint8_t op = gb_read_n(gb);

    uint16_t addr;

    switch(op) {
        default: /* invalid opcode PANIC! */
            EMU_ERR("Unknown opcode %02X encountered at: %04X", op, op_addr);
            break;

        case 0xC3: // Unconditional jump: (JP nn)
            addr = gb_read_nn(gb);
            GB_LOG_OP(op_addr, "JP $%04X", addr);
            gb->PC = addr;
            break;
        case 0xC2: // Conditional jump where zero flag = 0: (JP NZ, nn)
            addr = gb_read_nn(gb);
            GB_LOG_OP(op_addr, "JP NZ $%04X", addr);
            if(!gb->fz) {
                gb->PC = addr;
            }
            break;
        case 0xD2: // Conditional jump where carry flag = 0: (JP NC, nn)
            addr = gb_read_nn(gb);
            GB_LOG_OP(op_addr, "JP NC $%04X", addr);
            if(!gb->fc) {
                gb->PC = addr;
            }
            break;
        case 0xE9: // unconditional jump to HL: (JP HL)
            GB_LOG_OP(op_addr, "JP HL $%04X", gb->HL);
            gb->PC = gb->HL;
            break;
        
        
        case 0x00: GB_LOG_OP(op_addr, "NOP"); break;
        case 0xCB: /* Prefixed */ break;
    }
}

/* update functions */

void gb_update_timers(gb_state_t *gb) {

}
void gb_update_flags(gb_state_t *gb) {
    // convert flag vars into nibble for F reg
}

void gb_update(gb_state_t *gb) {}
