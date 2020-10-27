//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_SPRITE_RENDERER_H
#define BOLT_SPRITE_RENDERER_H

#include "transform.h"
#include "sprite.h"
#include "game_object.h"

namespace Bolt {

    class SpriteRenderer : public CustomComponent<SpriteRenderer> {
    private:
        int frame_counter;
    public:
        int updates_per_frame{0};
        vec2f center;
        Sprite sprite;
        SpriteRenderer(Sprite sprite);

        void onUpdate() override;
    };

}

#endif //BOLT_SPRITE_RENDERER_H
