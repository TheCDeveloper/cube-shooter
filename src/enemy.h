#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"


typedef struct Enemy_t {
    Sprite sprite;

    uint32_t health;
    uint32_t maxHealth;

    uint32_t speed;
} Enemy;


void Enemy_initialize(Enemy* enemy, uint32_t health, uint32_t speed);

void Enemy_draw(Enemy* enemy);
void Enemy_update(Enemy* enemy);

#endif // ENEMY_H
