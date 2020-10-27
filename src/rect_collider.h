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
        bool isInside(vec2f global_point) override;
        std::unique_ptr<Component> clone() const override;
    };

}

#endif //BOLT_RECT_COLLIDER_H
