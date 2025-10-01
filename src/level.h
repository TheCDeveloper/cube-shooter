#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "enemy.h"

#include <SDL3/SDL_events.h>


typedef struct Level_t {
    Player player;
    Sprite background;

    Enemy enemies[255];
    uint8_t enemyCount;
    uint8_t enemiesLeft;
} Level;


void Level_initialize(Level* level, uint8_t enemies);
void Level_deinitialize(Level* level);

void Level_event(Level* level, SDL_Event* event);
void Level_tick(Level* level, double deltaTime);
void Level_draw(Level* level);

#endif
