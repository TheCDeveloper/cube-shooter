#include "enemy.h"
#include <SDL3/SDL_render.h>

extern SDL_Renderer* renderer;


void Enemy_initialize(Enemy* enemy, uint32_t health, uint32_t speed) {
    if (!enemy) {
        return;
    }

    Sprite_initialize(&enemy->sprite, renderer, "res/cubes/1.bmp");
    enemy->sprite.display = (SDL_FRect) {0, 0, 50, 50};

    enemy->health = enemy->maxHealth = health;
    enemy->speed  = speed;
}


void Enemy_update(Enemy* enemy) {
    if (!enemy) {
        return;
    }
}


void Enemy_draw(Enemy* enemy) {
    if (!enemy) {
        return;
    }

    Sprite_draw(&enemy->sprite, renderer);
}
