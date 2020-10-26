//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "camera.h"

using namespace Bolt;

void Camera::onInit() {
    if (!main) main = this;
}
