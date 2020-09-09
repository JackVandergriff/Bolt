//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_SPRITE_RENDERER_H
#define BOLT_SPRITE_RENDERER_H

#include "transform.h"
#include "sprite.h"
#include "game_object.h"

class SpriteRenderer : public Component {
private:
    Transform* transform;
public:
    int frame{0};
    vec2f center;
    Sprite sprite;
    SpriteRenderer(Sprite);

    void onAttach() override;
    void onUpdate() override;
    int getFrame() const;
};


#endif //BOLT_SPRITE_RENDERER_H
