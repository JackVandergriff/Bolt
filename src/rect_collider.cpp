//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "rect_collider.h"
#include "geometry.h"
#include "transform.h"

using namespace Bolt;

bool RectCollider::isInside(vec2f global_point) {
    return inRect(transform->globalToLocal(global_point), collision);
}

std::unique_ptr<Component> RectCollider::clone() const {
    return std::make_unique<RectCollider>(*this);
}