//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "animation.h"

#include <SDL.h>

using namespace Bolt;

recti Animation::operator[](int index) const {
    return frames[index];
}

int Animation::size() const {
    return frames.size();
}

Animation::Animation(std::vector<recti> frames) : frames(frames) {}

Animation::Animation(recti frame) : frames{frame} {}

void Animation::advance() {
    frame = (frame + 1) % size();
}

void Animation::retreat() {
    frame = (frame + size() - 1) % size();
}

recti Animation::getFrame() const {
    return frames[frame];
}

void Animation::addFrame(recti new_frame) {
    frames.push_back(new_frame);
}

void Animation::reset() {
    frame = 0;
}

void Animation::setFrame(int new_frame) {
    frame = new_frame % size();
}

recti Animation::getFrameSize() const {
    return {0, 0, frames[0].w, frames[0].h};
}

Animation Bolt::generateTrivialAnimation(const std::shared_ptr<Texture>& texture) {
    recti position;
    SDL_QueryTexture(texture->getTexture(), nullptr, nullptr, &position.w, &position.h);
    return Animation(position);
}

Animation Bolt::generateSimpleAnimation(const std::shared_ptr<Texture>& texture, recti first_frame, int num_frames) {
    vec2i extents;
    SDL_QueryTexture(texture->getTexture(), nullptr, nullptr, &extents.x, &extents.y);

    vec2i advance_by{first_frame.w, 0};
    vec2i offset;
    Animation to_return;

    if (num_frames == 0) num_frames = INT16_MAX;
    for (int i = 0; i < num_frames; ++i) {
        to_return.addFrame(first_frame + offset);
        offset += advance_by;
        if ((offset.x + first_frame.w) > extents.x) {
            offset.x = 0;
            offset.y += first_frame.h;
            if ((offset.y + first_frame.h) > extents.y) {
                break;
            }
        }
    }

    return to_return;
}
