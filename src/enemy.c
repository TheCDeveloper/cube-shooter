#include "enemy.h"
#include "player.h"
#include <SDL3/SDL_render.h>
#include <math.h>

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


void Enemy_update(Enemy* enemy, float deltatime, Player* player) {
    if (!enemy || !player) {
        return;
    }

    float dist = hypot(
        enemy->sprite.display.x - player->sprite.display.x,
        enemy->sprite.display.y - player->sprite.display.y
    );

    enemy->sprite.display.x -= ((float) (enemy->sprite.display.x - player->sprite.display.x) / dist) * 100.0f * deltatime;
    enemy->sprite.display.y -= ((float) (enemy->sprite.display.y - player->sprite.display.y) / dist) * 100.0f * deltatime;

    if (SDL_Co)
}


void Enemy_draw(Enemy* enemy) {
    if (!enemy) {
        return;
    }

    Sprite_draw(&enemy->sprite, renderer);
}
