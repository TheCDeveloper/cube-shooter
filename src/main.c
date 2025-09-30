#include <SDL3/SDL.h>
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#include "level.h"

#include <stdio.h>


#define MAX_ENEMIES 128


SDL_Renderer* renderer;


int main() {
    // SDL Initialization
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "%s", SDL_GetError());
        return 1;
    }

    SDL_Window* window;
    SDL_CreateWindowAndRenderer(
        "Cube shooter",
        800,
        450,
        SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_HIDDEN,
        &window, &renderer);

    if (!window || !renderer) {
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "%s", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    SDL_DisplayID display = SDL_GetDisplayForWindow(window);
    const SDL_DisplayMode* displayMode = SDL_GetCurrentDisplayMode(display);

    if (displayMode) {
        int width  = displayMode->w * 0.75f;
        int height = width * (9.0f / 16.0f);
        int x      = (displayMode->w /2.0f) - (width / 2.0f);
        int y      = (displayMode->h /2.0f) - (height / 2.0f);

        printf("[Main] Optimal resolution: %d x %d\n", width, height);

        SDL_SetWindowSize(window, width, height);
        SDL_SetWindowPosition(window, x, y);
    }

    SDL_ShowWindow(window);

    SDL_SetWindowResizable(window, true);
    SDL_SetRenderVSync(renderer, 1);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


    // Game initalization
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    Level level;
    Level_initialize(&level, windowWidth, windowHeight, 5);


    // deltatime
    uint64_t last = SDL_GetPerformanceCounter();
    uint64_t freq = SDL_GetPerformanceFrequency();


    // Game loop
    bool running = true;

    while (running) {
        uint64_t now = SDL_GetPerformanceCounter();
        float deltatime = (float) (now - last) / freq;
        last = now;


        // Game tick
        Level_tick(&level, deltatime);


        // Rendering
        SDL_RenderClear(renderer);
        Level_draw(&level);
        SDL_RenderPresent(renderer);


        // Window events
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }

            Level_event(&level, &e);
        }
    }


    // Cleanup
    Level_deinitialize(&level);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
