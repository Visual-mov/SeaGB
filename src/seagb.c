#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "rom.h"
#include "gb.h"
#include "common.h"

int main(int argc, char *argv[]) {
    /* init SDL */
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        EMU_ERR("Couldn't initialize SDL: %s", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("SeaGB", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
    if(!window) {
        EMU_ERR("Couldn't initialize window: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    SDL_SetWindowResizable(window, SDL_FALSE);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        EMU_ERR("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* application loop */
    SDL_Event event;
    uint64_t p_freq = SDL_GetPerformanceFrequency();

    const double secs_per_frame = (double) 1 / FPS_CAP;
    double frame_time = 0;
    uint64_t frame_start = 0;
    int active = 1;
    
    while(active) {
        frame_start = SDL_GetPerformanceCounter();

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                active = 0;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        frame_time = (double) (SDL_GetPerformanceCounter() - frame_start)/p_freq;

        if (frame_time < secs_per_frame) {
            double delay = (secs_per_frame - frame_time) * 1000.0;
            if (delay > 0)
                SDL_Delay(delay);

            // Busy-wait the remainder (for sub-ms accuracy)
            while ((double)(SDL_GetPerformanceCounter() - frame_start)/p_freq < secs_per_frame);
        }

        double duration = (double) (SDL_GetPerformanceCounter() - frame_start)/p_freq;
        printf("FPS: %.3f\n", 1.0/duration);
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