#include <SDL3/SDL.h>
#include "level.h"

#define MAX_ENEMIES 128


SDL_Renderer* renderer;


int main() {
    // SDL Initialization
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "%s", SDL_GetError());
        return 1;
    }

    SDL_Window* window;
    SDL_CreateWindowAndRenderer("Cube shooter", 1280, 720, SDL_WINDOW_HIGH_PIXEL_DENSITY, &window, &renderer);

    if (!window || !renderer) {
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "%s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderVSync(renderer, 1);


    // Game initalization
    Level level;
    Level_initialize(&level, 4);


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
