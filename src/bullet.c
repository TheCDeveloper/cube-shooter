#include "bullet.h"
#include "sprite.h"
#include <SDL3/SDL_render.h>
#include <math.h>

extern SDL_Renderer* renderer;


void Bullet_initialize(Bullet *bullet, float x, float y, float rotation, uint32_t damage) {
    if (!bullet) {
        return;
    }

    Sprite_initialize(&bullet->sprite, renderer, "res/bullet.bmp");
    bullet->sprite.display = (SDL_FRect) {x, y, 25, 25};
    bullet->sprite.rotation = rotation;

    bullet->active = true;
    bullet->damage = damage;
}


void Bullet_update(Bullet* bullet, float deltatime) {
    if (!bullet) {
        return;
    }

    bullet->sprite.display.x += cos(bullet->sprite.rotation * (M_PI / 180.0f)) * 250.0f * deltatime;
    bullet->sprite.display.y += sin(bullet->sprite.rotation * (M_PI / 180.0f)) * 250.0f * deltatime;


    if (bullet->sprite.display.x < -25 || bullet->sprite.display.x > 800 ||
        bullet->sprite.display.y < -25 || bullet->sprite.display.y > 450) {
        bullet->active = false;
    }
}
