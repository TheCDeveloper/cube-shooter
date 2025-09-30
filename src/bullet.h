#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"
#include <stdbool.h>


typedef struct Bullet_t {
    bool active;
    Sprite sprite;

    uint32_t damage;
} Bullet;


void Bullet_initialize(Bullet* bullet, float x, float y, float rotation, uint32_t damage);

void Bullet_update(Bullet* bullet, float deltatime);

#endif
