//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_ANIMATION_H
#define BOLT_ANIMATION_H

#include <vector>

#include "texture.h"
#include "utility.h"

namespace Bolt {

    class Animation {
    private:
        std::vector<recti> frames{};
        int frame{0};
    public:
        recti operator[](int index) const;
        recti getFrame() const;
        int size() const;

        void advance();
        void retreat();
        void setFrame(int new_frame);
        void reset();
        void addFrame(recti new_frame);


        Animation(std::vector<recti> frames);
        Animation(recti frame);
        Animation() = default;
    };

    Animation generateTrivialAnimation(const Texture* texture);
    Animation generateSimpleAnimation(const Texture* texture, recti size, vec2i upper_corner = {}, int num_frames = 0);
}

#endif //BOLT_ANIMATION_H
