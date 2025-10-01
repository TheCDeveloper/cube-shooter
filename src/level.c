#include "level.h"
#include "enemy.h"
#include "player.h"
#include <stdlib.h>


extern SDL_Renderer* renderer;


void Level_initialize(Level *level, uint8_t enemies) {
    if (!level) {
        return;
    }


    Player_initialize(&level->player);
    Sprite_initialize(&level->background, renderer, "res/background.bmp");
    level->background.display = (SDL_FRect) {0, 0, 800, 450};
    
    level->enemyCount  = enemies;
    level->enemiesLeft = enemies;

    for (size_t i = 0; i < 255; i++) {
        Enemy_initialize(&level->enemies[i], 0, 0);

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
