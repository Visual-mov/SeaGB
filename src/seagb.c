#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "rom.h"
#include "gb.h"
#include "common.h"

int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        EMU_ERR("Couldn't initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("SeaGB", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    if(!window) {
        EMU_ERR("Couldn't initialize window: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        EMU_ERR("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    int active = 1;
    
    while(active) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                active = 0;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        //SDL_Delay(10); // Small delay to prevent busy-waiting
    }

    SDL_DestroyWindow(window);
    SDL_Quit();


    // rom_context_t *rom = load_rom("./rom/tetris.gb");
    // gb_state_t *gb = gb_init(rom);
    
    // EMU_LOG("emulator initialized");
    // gb_execute_cycle(gb);
    // gb_execute_cycle(gb);
    // gb_execute_cycle(gb);
    // gb_execute_cycle(gb);


    // free_rom(rom);
    // free_gb(gb);

    return 0;
}