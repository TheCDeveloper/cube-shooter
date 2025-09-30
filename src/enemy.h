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


void Enemy_initialize(Enemy* enemy, int windowWidth, int windowHeight, uint32_t health, uint32_t speed);

void Enemy_resizeEvent(Enemy* enemy, int oldWidth, int oldHeight, int newWidth, int newHeight);
void Enemy_update(Enemy* enemy, float deltatime, Player* player);
void Enemy_draw(Enemy* enemy);

#endif // ENEMY_H
