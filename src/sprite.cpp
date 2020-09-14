//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "sprite.h"
#include "animation.h"

using namespace Bolt;

int Sprite::getFrames() const {
    return animations[animation_index].size();
}

SDL_Texture* Sprite::getTexture() const {
    return texture.get()->getTexture();
}

recti Sprite::getSource() const {
    return animations[animation_index].getFrame();
}

Sprite::Sprite(std::shared_ptr<Texture> texture, std::vector<Animation> animations) : texture(texture), animations(animations) {}

void Sprite::addAnimation(Animation animation) {
    animations.push_back(animation);
}

Animation& Sprite::getAnimation() {
    return animations[animation_index];
}
