//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_SPRITE_H
#define BOLT_SPRITE_H

#include "texture.h"
#include "animation.h"
#include "utility.h"

#include <memory>
#include <vector>

namespace Bolt {

    class BOLT_EXPORT Sprite {
    private:
        std::shared_ptr<Texture> texture;
        std::vector<Animation> animations;
    public:
        int animation_index{0};
        double scale{1.0f};

        Sprite(std::shared_ptr<Texture> texture, std::vector<Animation> animations);
        void addAnimation(Animation animation);

        int getFrames() const;
        SDL_Texture* getTexture() const;
        recti getSource() const;
        Animation& getAnimation();
    };

}

#endif //BOLT_SPRITE_H