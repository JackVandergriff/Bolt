//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "component.h"
#include "game_object.h"
#include "window_manager.h"

using namespace Bolt;

GameObject *Component::getOwner() const {
    return owner;
}

Component::~Component() {
    WindowManager::unregisterHandler(this);
}

Transform* Component::getTransform() const {
    return transform;
}
