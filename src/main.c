#include <SDL3/SDL.h>
#include "player.h"
#include "enemy.h"
#include <time.h>

#define MAX_ENEMIES 256


SDL_Renderer* renderer;


int main() {
    // SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "%s", SDL_GetError());
        return 1;
    }

    SDL_Window* window;
    SDL_CreateWindowAndRenderer("Cube shooter", 800, 450, SDL_WINDOW_HIGH_PIXEL_DENSITY, &window, &renderer);

    if (!window || !renderer) {
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "%s", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    // Game initalization
    Sprite background;
    Sprite_initialize(&background, renderer, "res/background.bmp");
    background.display = (SDL_FRect) {0, 0, 800, 450};

    Player player;
    Player_initialize(&player);

    Enemy enemies[MAX_ENEMIES];
    size_t enemyCount = 1;

    Enemy_initialize(&enemies[0], 100, 10);

    player.sprite.display.x = 100;
    player.sprite.display.y = 40;
    player.sprite.rotation  = 45;


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
        for (size_t i = 0; i < enemyCount; i++) {
            Enemy* enemy = &enemies[i];

            if (enemy->health > 0) {
                Enemy_update(enemy, deltatime, &player);
            }
        }

        Player_update(&player, deltatime);


        // Rendering
        SDL_RenderClear(renderer);
        Sprite_draw(&background, renderer);
        Player_draw(&player);

        for (size_t i = 0; i < enemyCount; i++) {
            Enemy* enemy = &enemies[i];

            if (enemy->health > 0) {
                Enemy_draw(enemy);
            }
        }

        SDL_RenderPresent(renderer);


        // Window events
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP) {
                Player_keyEvent(&player, e.type, e.key.scancode);
            }
        }
    }


    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
