#include "bullet.h"
#include "sprite.h"
#include <SDL3/SDL_render.h>
#include <math.h>

extern SDL_Renderer* renderer;


void Bullet_initialize(Bullet *bullet, int w, int h, float x, float y, float rotation, uint32_t damage) {
    if (!bullet) {
        return;
    }

    float scaleX = (float) w / 1280.0f;
    float scaleY = (float) h / 720.0f;
    float scale  = scaleX > scaleY ? scaleX : scaleY;

    Sprite_initialize(&bullet->sprite, renderer, "res/bullet.bmp");
    bullet->sprite.display = (SDL_FRect) {x, y, 32 * scale, 32 * scale};
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
    if (bullet->sprite.display.x < -25 || bullet->sprite.display.x > 800 ||
        bullet->sprite.display.y < -25 || bullet->sprite.display.y > 450) {
        bullet->active = false;
    }
}
