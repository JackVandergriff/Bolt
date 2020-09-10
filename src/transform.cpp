//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "transform.h"

using namespace Bolt;

Geometry Transform::globalGeometry() const {
    GameObject* cur_owner = owner;
    Geometry global_geometry;
    while (cur_owner != nullptr) {
        global_geometry = stripGeometry(global_geometry, cur_owner->getComponent<Transform>()->local_geometry);
        cur_owner = cur_owner->getOwner();
    }

    return global_geometry;
}
