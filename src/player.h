#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "bullet.h"


typedef struct Player_t {
    int windowWidth;
    int windowHeight;
    Sprite sprite;

    int32_t health;
    int32_t maxHealth;

    float velocityX;
    float velocityY;

    int8_t acceleration;
    int8_t rotation;

    Bullet bullets[100];
    size_t bulletCount;
} Player;


void Player_initialize(Player* player, int windowWidth, int windowHeight);
void Player_deinitialize(Player* player);

void Player_keyEvent(Player* player, uint32_t type, SDL_Scancode code);
void Player_resizeEvent(Player *player, int oldWidth, int oldHeight, int newWidth, int newHeight);
void Player_shoot(Player* player);

void Player_update(Player* player, double deltatime);
void Player_draw(Player* player);

#endif // PLAYER_H
