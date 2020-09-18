//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_RECT_COLLIDER_H
#define BOLT_RECT_COLLIDER_H

#include "collider.h"

namespace Bolt {

    class RectCollider : public Collider {
    public:
        rectf collision;
        bool isInside(vec2f) override;
    };

}

#endif //BOLT_RECT_COLLIDER_H
