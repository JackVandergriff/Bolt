//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "sprite_renderer.h"
#include "window_manager.h"

#include <iostream>

using namespace Bolt;

SpriteRenderer::SpriteRenderer(Sprite sprite) : sprite(sprite){}

void SpriteRenderer::onUpdate() {
    if (updates_per_frame > 0) {
        frame_counter = (frame_counter + 1) % updates_per_frame;
        if (frame_counter == 0) sprite.getAnimation().advance();
    }
    rectf local = sprite.getAnimation().getFrameSize(); // Force conversion to rectf for source - center calculation
    auto dest = transform->localToGlobal(local - center);
    WindowManager::render({sprite.getTexture(), sprite.getSource(), dest});
}
