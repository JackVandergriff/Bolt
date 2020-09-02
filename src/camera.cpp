//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "camera.h"

void Camera::onAttach(GameObject* new_owner) {
    transform = owner->getComponent<Transform>();
}

Camera::Camera() {
    if (!main) main = this;
}
