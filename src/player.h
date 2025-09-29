#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"


typedef struct Player_t {
    Sprite sprite;

    uint32_t health;
    uint32_t maxHealth;

    float velocityX;
    float velocityY;

    int8_t acceleration;
    int8_t rotation;
} Player;


void Player_initialize(Player* player);

void Player_keyEvent(Player* player, uint32_t type, SDL_Scancode code);
void Player_update(Player* player, double deltatime);
void Player_draw(Player* player);

#endif // PLAYER_H
