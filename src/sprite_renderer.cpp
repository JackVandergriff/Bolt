//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "sprite_renderer.h"
#include "window_manager.h"

#include <iostream>

using namespace Bolt;

void SpriteRenderer::onAttach() {
    transform = owner->getComponent<Transform>();
    if (transform == nullptr) {
        throw "No transform on Object";
    }
}

int SpriteRenderer::getFrame() const {
    return frame;
}

SpriteRenderer::SpriteRenderer(Sprite s) : sprite(s){}

void SpriteRenderer::onUpdate() {
    auto source = sprite.getSource();
    auto dest = stripGeometry(source - center, transform->globalGeometry());
    if (frame > 0 && frame <= sprite.getFrames()) source.x += (frame - 1) * source.w;
    WindowManager::render({sprite.getTexture(), source, dest});
}
