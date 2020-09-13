//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "animation.h"

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

Animation Bolt::generateTrivialAnimation(const Texture* texture) {
    recti position;
    SDL_QueryTexture(texture->getTexture(), nullptr, nullptr, &position.w, &position.h);
    return Animation(position);
}

Animation Bolt::generateSimpleAnimation(const Texture* texture, recti size, vec2i upper_corner, int num_frames) {
    vec2i extents;
    SDL_QueryTexture(texture->getTexture(), nullptr, nullptr, &extents.x, &extents.y);

    vec2i advance_by{size.w, 0};
    Animation to_return;

    if (num_frames == 0) num_frames = INT16_MAX;
    for (int i = 0; i < num_frames; ++i) {
        to_return.addFrame(size + upper_corner);
        upper_corner += advance_by;
        if ((upper_corner.x + size.w) > extents.x) {
            upper_corner.x = 0;
            upper_corner.y += size.h;
            if ((upper_corner.y + size.h) > extents.y) {
                break;
            }
        }
    }

    return to_return;
}
