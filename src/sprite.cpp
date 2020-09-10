//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "sprite.h"

using namespace Bolt;

Sprite::Sprite(std::shared_ptr<Texture> texture, rectf pos, int frames) : texture(texture) {
    if (pos.h == 0 || pos.w == 0) {
        int w, h;
        SDL_QueryTexture(texture->getTexture(), nullptr, nullptr, &w, &h);
        source = {0, 0, (float)w, (float)h};
    } else {
        source = pos;
    }
    this->frames = frames;
}

int Sprite::getFrames() const {
    return frames;
}

SDL_Texture* Sprite::getTexture() const {
    return texture.get()->getTexture();
}

rectf Sprite::getSource() const {
    return source;
}
