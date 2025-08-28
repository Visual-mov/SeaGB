#include "rom.h"
#include "common.h"

#include <stdlib.h>
#include <stdio.h>

rom_context_t *load_rom(char *path) {
    FILE *fp;
    if((fp = fopen(path, "rb")) == NULL) {
        EMU_ERR("Failed to load cartridge ROM");
    }
    rom_context_t *ctx = (rom_context_t*) malloc(sizeof(rom_context_t));

    // Get the rom size
    if(fseek(fp, 0, SEEK_END) != 0) {
        EMU_ERR("I/O Error.");
    }

    long file_size = ftell(fp);
    rewind(fp);
    
    printf("\"%s\" loaded, size: %ld bytes.\n", path, file_size);
    ctx->rom = (uint8_t *) malloc(file_size);

    if(fread(ctx->rom, 1, file_size, fp) != file_size) {
        EMU_ERR("Error reading from ROM file.");
    }

    printf("%02x\n", ctx->rom[0x01]);

    // NOTE: for debug use right now
    // Read the title (16 bytes, padded with 00)
    // char *title = (char*) malloc(16);
    // fseek(fp, 0x134, SEEK_SET);
    // fread(title, 1, 16, fp);
    // ctx->title = title;

    // // Read the manufacturer code (TBD)

    // // read the gameboy color and super gameboy flags
    // ctx->gbc_flag = 0;
    // fseek(fp, 0x143, SEEK_SET);
    // fread(&(ctx->gbc_flag), 1, 1, fp);
    // fseek(fp, 0x146, SEEK_SET);

    // uint8_t header_buf[4] = {0, 0, 0, 0};
    // if(fread(&header_buf, 1, 4, fp) < 4) {
    //     EMU_ERR("I/O Error.");
    // }
    // ctx->sgb_flag = header_buf[0];
    // ctx->type = header_buf[1];
    // ctx->rom_size = header_buf[2];
    // ctx->ram_size = header_buf[3];
    
    // printf("title: %s\ngbc flag: %02x\nsgb flag: %02x\ncart type: %02x\nrom size: %02x\nram size: %02x\n",
    //     title, ctx->gbc_flag, ctx->sgb_flag, ctx->type, ctx->rom_size, ctx->ram_size);

    // test read title:
    fclose(fp);
    return ctx;
}

void free_rom(rom_context_t *ctx) {
    if(!ctx)
        return;
    free(ctx->title);
    free(ctx);
}