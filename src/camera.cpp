//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "camera.h"

void Camera::onAttach() {
    transform = owner->getComponent<Transform>();
}

Camera::Camera() {
    if (!main) main = this;
}
