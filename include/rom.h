#ifndef ROM_H
#define ROM_H

#include <stdint.h>

typedef enum cart_type {
    MBC_NO_MBC = 0x00,
    MBC_MBC1   = 0x01,
    // MBC_MBC1_RAM,
    // MBC_MBC1_RAM_BATTERY,
    // MBC_MBC2,
    // MBC_MBC2_BATTERY,
    // MBC_ROM_RAM,
    // MBC_ROM_RAM_BATTERY,
    // MBC_MMM01,
    // MBC_MMM01_RAM,
    // MBC_MMM01_RAM_BATTERY,
    // MBC_MBC3_TIMER_BATTERY,
    // MBC_MBC3_TIMER_RAM_BATTERY,
    // MBC_MBC3,
    // MBC_MBC3_RAM,
    // MBC_MBC3_RAM_BATTERY,
    // MBC_MBC5,
    // MBC_MBC5_RAM,
    // MBC_MBC5_RAM_BATTERY,
    // MBC_MBC5_RUMBLE,
    // MBC_MBC5_RUMBLE_RAM,
    // MBC_MBC5_RUMBLE_RAM_BATTERY,
    // MBC_MBC6,
    // MBC_MBC7_SENSOR_RUMBLE_RAM_BATTERY,
    // MBC_POCKET_CAMERA,
    // MBC_BANDAI_TAMA5,
    // MBC_HuC3,
    // MBC_HuC1_RAM_BATTERY,
} cart_type;

// NOTE: this structure might not be needed
typedef struct rom_context_t {
    char *title;
    uint8_t sgb_flag, gbc_flag;  // SNES super gameboy and gameboy color flags
    cart_type type;
    uint8_t rom_size, ram_size;
    uint8_t *rom;      // ROM machine code array
} rom_context_t;

rom_context_t *load_rom(char *path);
void free_rom(rom_context_t *ctx);

#endif