//
// Created by jack on 8/19/20.
//

#include "texture.h"

Texture::~Texture() {
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::getTexture() const {
    return texture;
}
