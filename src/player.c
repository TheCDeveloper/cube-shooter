#include "player.h"
#include "bullet.h"
#include <SDL3/SDL_render.h>
#include <stdlib.h>
#include <stdio.h>
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

    player->bulletCount = 0;
}


void Player_deinitialize(Player* player) {
    if (!player) {
        return;
    }


    Sprite_deinitialize(&player->sprite);

    for (size_t i = 0; i < player->bulletCount; i++) {
        Sprite_deinitialize(&player->bullets[i].sprite);
    }
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
        } else if (code == SDL_SCANCODE_SPACE) {
            Player_shoot(player);
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


void Player_shoot(Player *player) {
    if (!player || player->bulletCount >= 100) {
        return;
    }


    Bullet* bullet = &player->bullets[player->bulletCount];

    for (size_t i = 0; i < player->bulletCount; i++) {
        if (!player->bullets[i].active) {
            bullet = &player->bullets[i];
            bullet->sprite.display.x = player->sprite.display.x;
            bullet->sprite.display.y = player->sprite.display.y;
            bullet->sprite.rotation  = player->sprite.rotation;
            bullet->active = true;

            return;
        }
    }

    Bullet_initialize(bullet, player->sprite.display.x, player->sprite.display.y, player->sprite.rotation, 1);
    bullet->active = true;
    player->bulletCount++;
}


void Player_update(Player* player, double deltatime) {
    if (!player) {
        return;
    }

    if (player->health < 0) {
        printf("Player died 💀\nThe Game will now crash.\n");
        abort();
    }


    // Movement
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


    // Friction
    player->velocityX -= player->velocityX * deltatime;
    player->velocityY -= player->velocityY * deltatime;


    // Bullets
    for (size_t i = 0; i < player->bulletCount; i++) {
        if (!player->bullets[i].active) {
            continue;
        }

        Bullet_update(&player->bullets[i], deltatime);
    }
}


void Player_draw(Player* player) {
    if (!player || !renderer) {
        return;
    }


    // Bullets and player
    for (size_t i = 0; i < player->bulletCount; i++) {
        if (!player->bullets[i].active) {
            continue;
        }

        Sprite_draw(&player->bullets[i].sprite, renderer);
    }

    Sprite_draw(&player->sprite, renderer);


    // Healthbar
    SDL_FRect base = {
        (player->sprite.display.x - 15),
        (player->sprite.display.y - 30),
        80,
        10
    };

    SDL_FRect fill = {
        base.x + 2, base.y + 2,
        (((float) player->health / player->maxHealth) * base.w) - 4, base.h - 4
    };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderFillRect(renderer, &base);

    SDL_SetRenderDrawColor(renderer, 0, 255, 25, 255);
    SDL_RenderFillRect(renderer, &fill);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
