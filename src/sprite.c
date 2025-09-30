#include "sprite.h"


void Sprite_initialize(Sprite *sprite, SDL_Renderer* renderer, const char *texturepath) {
    if (!sprite || !renderer || !texturepath) {
        return;
    }


    SDL_Surface* surf = SDL_LoadBMP(texturepath);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_DestroySurface(surf);

    float w, h;
    SDL_GetTextureSize(text, &w, &h);

    sprite->texture = text;
    sprite->crop    = (SDL_FRect) {0, 0, w, h};

    sprite->display  = (SDL_FRect) {0, 0, 100, 100};
    sprite->rotation = 0;
}


void Sprite_deinitialize(Sprite *sprite) {
    if (!sprite) {
        return;
    }

    SDL_Texture* texture = sprite->texture;

    if (texture) {
        SDL_DestroyTexture(texture);
    }
}


void Sprite_draw(Sprite* sprite, SDL_Renderer* renderer) {
    if (!sprite || !renderer) {
        return;
    }
    

    SDL_FPoint center = {
        sprite->display.w / 2.0f,
        sprite->display.h / 2.0f
    };

    SDL_RenderTextureRotated(
        renderer,
        sprite->texture,
        &sprite->crop,
        &sprite->display,
        sprite->rotation,
        &center,
        SDL_FLIP_NONE
    );
}
