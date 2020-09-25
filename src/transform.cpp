//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "transform.h"
#include "window_manager.h"

using namespace Bolt;

Geometry Transform::globalGeometry() const {
    GameObject* cur_owner = owner;
    Geometry global_geometry;
    while (cur_owner != WindowManager::dummy) {
        global_geometry = stripGeometry(global_geometry, cur_owner->getTransform()->local_geometry);
        cur_owner = cur_owner->getOwner();
    }

    return global_geometry;
}