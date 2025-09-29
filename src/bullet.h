#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"


typedef struct Bullet_t {
    Sprite sprite;
    uint32_t damage;
} Bullet;


void Bullet_initialize(Bullet* bullet, float rotation, uint32_t damage);

void Bullet_update(Bullet* bullet, float deltatime);

#endif