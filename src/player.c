#include "player.h"
#include "sprite.h"
#include <math.h>

extern SDL_Renderer* renderer;


void Player_initialize(Player *player) {
    if (!player || !renderer) {
        return;
    }

    Sprite_initialize(&player->sprite, renderer, "res/player.bmp");
    player->sprite.display = (SDL_FRect) {0, 0, 50, 50};

    player->health = player->maxHealth = 100;

    player->velocityX = 0;
    player->velocityY = 0;

    player->acceleration = 0;
    player->rotation     = 0;
}


void Player_keyEvent(Player* player, uint32_t type, SDL_Scancode code) {
    if (!player) {
        return;
    }

    if (type == SDL_EVENT_KEY_DOWN) {
        if (code == SDL_SCANCODE_W || code == SDL_SCANCODE_UP) {
            player->acceleration = 1;
        } else if (code == SDL_SCANCODE_S || code == SDL_SCANCODE_DOWN) {
            player->acceleration = -1;
        }
    } else if (type == SDL_EVENT_KEY_UP) {
        if (code == SDL_SCANCODE_W || code == SDL_SCANCODE_UP ||
            code == SDL_SCANCODE_S || code == SDL_SCANCODE_DOWN) {
            player->acceleration = 0;
        }
    }
}


void Player_update(Player* player, double deltatime) {
    if (!player) {
        return;
    }

    player->sprite.rotation += player->rotation * deltatime;

    if (player->sprite.rotation > 360) {
        player->sprite.rotation = 360;
    } else if (player->sprite.rotation < 0) {
        player->sprite.rotation = 0;
    }

    player->velocityX -= cos(player->sprite.rotation * (M_PI / 180.0f)) * player->acceleration * 5.0f * deltatime;
    player->velocityY -= sin(player->sprite.rotation * (M_PI / 180.0f)) * player->acceleration * 5.0f * deltatime;

    
    player->sprite.display.x += player->velocityX;
    player->sprite.display.y += player->velocityY;
}


void Player_draw(Player* player) {
    if (!player || !renderer) {
        return;
    }

    Sprite_draw(&player->sprite, renderer);
}
