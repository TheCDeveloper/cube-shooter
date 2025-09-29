#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL_render.h>


typedef struct Sprite_t {
    SDL_Texture* texture;
    SDL_FRect crop;

    SDL_FRect display;
    float rotation;
} Sprite;


void Sprite_initialize(Sprite* sprite, SDL_Renderer* renderer, const char* texturepath);
Sprite* Sprite_create(SDL_Renderer* renderer, const char* texturepath);
void Sprite_destroy(Sprite* sprite);

void Sprite_draw(Sprite* sprite, SDL_Renderer* renderer);


#endif // SPRITE_H
