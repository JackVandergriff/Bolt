//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_SPRITE_H
#define BOLT_SPRITE_H

#include "texture.h"
#include "utility.h"

#include <memory>

class Sprite {
private:
    std::shared_ptr<Texture> texture;
    rectf source;
    int frames;
public:
    Sprite(std::shared_ptr<Texture>, rectf={0,0,0,0}, int=0);

    float scale{1.0f};
    int getFrames() const;
    SDL_Texture* getTexture() const;
    rectf getSource() const;
};

#endif //BOLT_SPRITE_H