#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include <stdbool.h>

typedef struct Player_t Player;


typedef struct Enemy_t {
    bool alive;
    Sprite sprite;

    uint32_t health;
    uint32_t maxHealth;

    uint32_t speed;

    bool debounce;
    float debounceTime;
} Enemy;


void Enemy_initialize(Enemy* enemy, uint32_t health, uint32_t speed);

void Enemy_draw(Enemy* enemy);
void Enemy_update(Enemy* enemy, float deltatime, Player* player);

#endif // ENEMY_H
