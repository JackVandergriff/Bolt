//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "rect_collider.h"
#include "geometry.h"
#include "transform.h"

using namespace Bolt;

bool RectCollider::isInside(vec2f global_pos) {
    return inRect(transform->globalToLocal(global_pos), collision);
}
