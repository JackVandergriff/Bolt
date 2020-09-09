//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "texture.h"

Texture::~Texture() {
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::getTexture() const {
    return texture;
}
