#include "level.h"
#include "enemy.h"
#include "player.h"
#include <SDL3/SDL_events.h>
#include <stdlib.h>


extern SDL_Renderer* renderer;


void Level_initialize(Level *level, int windowWidth, int windowHeight, uint8_t enemies) {
    if (!level) {
        return;
    }


    level->windowWidth  = windowWidth;
    level->windowHeight = windowHeight;

    Player_initialize(&level->player, level->windowWidth, level->windowHeight);
    Sprite_initialize(&level->background, renderer, "res/background.bmp");
    level->background.display = (SDL_FRect) {0, 0, level->windowWidth, level->windowHeight};
    
    level->enemyCount  = enemies;
    level->enemiesLeft = enemies;

    for (size_t i = 0; i < 255; i++) {
        Enemy_initialize(&level->enemies[i], level->windowWidth, level->windowHeight, 0, 0);

        if (i < enemies) {
            level->enemies[i].alive  = true;
            level->enemies[i].health = level->enemies[i].maxHealth = 10;

            level->enemies[i].sprite.display.x = ((float) rand() / (float) RAND_MAX) * 800.0f;
            level->enemies[i].sprite.display.y = ((float) rand() / (float) RAND_MAX) * 450.0f;
        }
    }
}


void Level_deinitialize(Level *level) {
    if (!level) {
        return;
    }


    Sprite_deinitialize(&level->background);
    Player_deinitialize(&level->player);

    for (size_t i = 0; i < 256; i++) {
        Sprite_deinitialize(&level->enemies[i].sprite);
    }
}


void Level_event(Level *level, SDL_Event *event) {
    if (!level) {
        return;
    }


    Player_keyEvent(&level->player, event->type, event->key.scancode);

    if (event->type == SDL_EVENT_WINDOW_RESIZED) {
        level->background.display.w = event->window.data1;
        level->background.display.h = event->window.data2;

        Player_resizeEvent(&level->player, level->windowWidth, level->windowHeight, event->window.data1, event->window.data2);

        for (size_t i = 0; i < level->enemyCount; i++) {
            if (!level->enemies[i].alive) {
                continue;
            }

            Enemy* e = &level->enemies[i];
            Enemy_resizeEvent(e, level->windowWidth, level->windowHeight, event->window.data1, event->window.data2);
        }
        
        level->windowWidth = event->window.data1;
        level->windowHeight = event->window.data2;
    }
}


void Level_tick(Level *level, double deltaTime) {
    if (!level) {
        return;
    }


    Player_update(&level->player, deltaTime);

    for (size_t i = 0; i < level->enemyCount; i++) {
        if (level->enemies[i].alive) {
            Enemy_update(&level->enemies[i], deltaTime, &level->player);
        }
    }
}


void Level_draw(Level* level) {
    if (!level) {
        return;
    }


    Sprite_draw(&level->background, renderer);
    Player_draw(&level->player);

    for (size_t i = 0; i < level->enemyCount; i++) {
        if (level->enemies[i].alive) {
            Enemy_draw(&level->enemies[i]);
        }
    }
}
