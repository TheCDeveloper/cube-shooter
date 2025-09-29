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
        } else if (code == SDL_SCANCODE_A || code == SDL_SCANCODE_LEFT) {
            player->rotation = -1;
        } else if (code == SDL_SCANCODE_D || code == SDL_SCANCODE_RIGHT) {
            player->rotation = 1;
        }
    } else if (type == SDL_EVENT_KEY_UP) {
        if (code == SDL_SCANCODE_W || code == SDL_SCANCODE_UP ||
            code == SDL_SCANCODE_S || code == SDL_SCANCODE_DOWN) {
            player->acceleration = 0;
        } else if (code == SDL_SCANCODE_A || code == SDL_SCANCODE_LEFT ||
                   code == SDL_SCANCODE_D || code == SDL_SCANCODE_RIGHT) {
            player->rotation = 0;
        }
    }
}


void Player_update(Player* player, double deltatime) {
    if (!player) {
        return;
    }

    player->sprite.rotation += player->rotation * 200.0f * deltatime;

    if (player->sprite.rotation > 360) {
        player->sprite.rotation = 0;
    } else if (player->sprite.rotation < 0) {
        player->sprite.rotation = 360;
    }

    player->velocityX += cos(player->sprite.rotation * (M_PI / 180.0f)) * player->acceleration * 500.0f * deltatime;
    player->velocityY += sin(player->sprite.rotation * (M_PI / 180.0f)) * player->acceleration * 500.0f * deltatime;

    player->sprite.display.x += player->velocityX * deltatime;
    player->sprite.display.y += player->velocityY * deltatime;

    player->velocityX -= player->velocityX * deltatime;
    player->velocityY -= player->velocityY * deltatime;
}


void Player_draw(Player* player) {
    if (!player || !renderer) {
        return;
    }

    Sprite_draw(&player->sprite, renderer);
}
