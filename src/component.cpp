//
// Created by jack on 8/19/20.
//

#include "component.h"
#include "game_object.h"
#include "window_manager.h"

GameObject *Component::getOwner() const {
    return owner;
}

Component::~Component() {
    WindowManager::unregisterHandler(this);
}