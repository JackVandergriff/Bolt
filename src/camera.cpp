//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "camera.h"

using namespace Bolt;

void Camera::onAttach() {
    transform = owner->getComponent<Transform>();
}

Camera::Camera() {
    if (!main) main = this;
}
