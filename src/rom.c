#include "rom.h"
#include "common.h"

#include <stdlib.h>
#include <stdio.h>

rom_context_t *load_rom(char *path) {
    FILE *fp;
    if((fp = fopen(path, "rb")) == NULL) {
        EMU_ERR("Failed to load cartridge ROM");
    }
    rom_context_t *ctx = NULL;

    // Get the rom size
    if(fseek(fp, 0, SEEK_END) != 0) {
        EMU_ERR("I/O Error.");
        return ctx;
    }
    long rom_size = ftell(fp);
    printf("\"%s\" loaded, size: %ld bytes.\n", path, rom_size);
    rewind(fp);

    ctx = (rom_context_t*) malloc(sizeof(rom_context_t));

    // Read the title (16 bytes, padded with 00)
    char *title = (char*) malloc(16);
    fseek(fp, 0x134, SEEK_SET);
    fread(title, 1, 16, fp);
    ctx->title = title;

    // Read the manufacturer code (TBD)

    // read the gameboy color and super gameboy flags
    ctx->gbc_flag = 0;
    fseek(fp, 0x143, SEEK_SET);
    fread(&(ctx->gbc_flag), 1, 1, fp);
    fseek(fp, 0x146, SEEK_SET);

    uint8_t header_buf[4] = {0, 0, 0, 0};
    if(fread(&header_buf, 1, 4, fp) < 4) {
        EMU_ERR("I/O Error.");
    }
    ctx->sgb_flag = header_buf[0];
    ctx->type = header_buf[1];
    ctx->rom_size = header_buf[2];
    ctx->ram_size = header_buf[3];
    
    printf("title: %s\ngbc flag: %02x\nsgb flag: %02x\ncart type: %02x\nrom size: %02x\nram size: %02x\n",
        title, ctx->gbc_flag, ctx->sgb_flag, ctx->type, ctx->rom_size, ctx->ram_size);


    // for(int i = 0; i < 16; i++) {
    //     uint8_t byte = title[i];
    //     printf("%02x ", byte);
    // }


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