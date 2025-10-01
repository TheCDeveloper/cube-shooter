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
    bullet->sprite.display = (SDL_FRect) {x, y, 32, 32};
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

    // Delete bullet if out of bounds
    if (bullet->sprite.display.x < -32 || bullet->sprite.display.x > 1280 ||
        bullet->sprite.display.y < -32 || bullet->sprite.display.y > 720) {
        bullet->active = false;
    }
}
