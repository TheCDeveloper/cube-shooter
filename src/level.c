#include "level.h"
#include "enemy.h"
#include "player.h"
#include <stdlib.h>
#include <stdio.h>


extern SDL_Renderer* renderer;


void Level_initialize(Level *level, uint8_t enemies) {
    if (!level) {
        return;
    }


    level->round = 1;

    Player_initialize(&level->player);
    Sprite_initialize(&level->background, renderer, "res/background.bmp");
    level->background.display = (SDL_FRect) {0, 0, 1280, 720};
    
    level->enemyCount  = enemies;
    level->enemiesLeft = enemies;

    for (size_t i = 0; i < 255; i++) {
        Enemy_initialize(&level->enemies[i], 0, 0);

        if (i < enemies) {
            level->enemies[i].alive     = true;
            level->enemies[i].maxHealth = 8 + (2 * level->round);
            level->enemies[i].health    = level->enemies[i].maxHealth;

            SDL_FRect* display = &level->enemies[i].sprite.display;
            display->x = -250 + rand() % ((1253) + 250 + 1);
            display->y = -250 + rand() % ((970) + 250 + 1);
        }
    }
}


void Level_deinitialize(Level *level) {
    if (!level) {
        return;
    }


    Sprite_deinitialize(&level->background);
    Player_deinitialize(&level->player);

    for (size_t i = 0; i < 256; i++) {
        Sprite_deinitialize(&level->enemies[i].sprite);
    }
}


void Level_event(Level *level, SDL_Event *event) {
    if (!level) {
        return;
    }


    Player_keyEvent(&level->player, event->type, event->key.scancode);
}


void Level_tick(Level *level, double deltaTime) {
    if (!level) {
        return;
    }


    // Tick entities
    Player_update(&level->player, deltaTime);
    
    if (level->player.health <= 0) {
        printf("You died 💀\nRounds survived: %d\n\nThis game will now crash.\n", level->round);
        abort();
    }


    for (size_t i = 0; i < level->enemyCount; i++) {
        if (level->enemies[i].alive) {
            Enemy_update(&level->enemies[i], deltaTime, &level->player);


            // Enemy attack
            Enemy* enemy = &level->enemies[i];
            
            if (!enemy->debounce && SDL_HasRectIntersectionFloat(&enemy->sprite.display, &level->player.sprite.display)) {
                enemy->debounce = true;
                enemy->debounceTime = 0;
                level->player.health -= 1;
            } else {
                enemy->debounceTime += deltaTime;

                if (enemy->debounceTime > 0.25f) {
                    enemy->debounce = false;
                }
            }


            // Enemy damage
            for (size_t j = 0; j < level->player.bulletCount; j++) {
                if (!level->player.bullets[j].active) {
                    continue;
                }

                
                Bullet* bullet = &level->player.bullets[j];

                if (SDL_HasRectIntersectionFloat(&bullet->sprite.display, &enemy->sprite.display)) {
                    bullet->active = false;
                    enemy->health -= bullet->damage;

                    if (enemy->health <= 0) {
                        enemy->alive = false;
                        level->enemiesLeft--;
                    }
                }
            }
        }
    }


    // Level
    if (level->enemiesLeft == 0) {
        printf("All enemies died! Starting round %d\n", level->round);


        if (level->round >= 10) {
            printf("You won!\n");
            exit(0);
        }


        level->round++;
        level->enemyCount += 2;
        level->enemiesLeft = level->enemyCount;

        for (size_t i = 0; i < level->enemyCount; i++) {
            Enemy* enemy = &level->enemies[i];
            enemy->alive = true;
            enemy->health = enemy->maxHealth = 8 + (2 * level->round);
            
            SDL_FRect* display = &enemy->sprite.display;
            display->x = -250 + rand() % ((1253) + 250 + 1);
            display->y = -250 + rand() % ((970) + 250 + 1);
        }
    }
}


void Level_draw(Level* level) {
    if (!level) {
        return;
    }


    Sprite_draw(&level->background, renderer);
    Player_draw(&level->player);

    for (size_t i = 0; i < level->enemyCount; i++) {
        if (level->enemies[i].alive) {
            Enemy_draw(&level->enemies[i]);
        }
    }
}
