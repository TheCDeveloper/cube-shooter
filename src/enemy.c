#include "enemy.h"
#include "player.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <math.h>

extern SDL_Renderer* renderer;


void Enemy_initialize(Enemy* enemy, uint32_t health, uint32_t speed) {
    if (!enemy) {
        return;
    }

    Sprite_initialize(&enemy->sprite, renderer, "res/cubes/1.bmp");
    enemy->sprite.display = (SDL_FRect) {0, 0, 64, 64};

    enemy->alive  = false;
    enemy->health = enemy->maxHealth = health;
    enemy->speed  = speed;

    enemy->debounce     = false;
    enemy->debounceTime = 0.0f;
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
}


void Enemy_draw(Enemy* enemy) {
    if (!enemy) {
        return;
    }

    Sprite_draw(&enemy->sprite, renderer);

    SDL_FRect base = {
        (enemy->sprite.display.x - 15),
        (enemy->sprite.display.y - 30),
        94,
        10
    };

    SDL_FRect fill = {
        base.x + 2, base.y + 2,
        (((float) enemy->health / enemy->maxHealth) * base.w) - 4, base.h - 4
    };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderFillRect(renderer, &base);

    SDL_SetRenderDrawColor(renderer, 255, 25, 25, 255);
    SDL_RenderFillRect(renderer, &fill);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
