//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_CAMERA_H
#define BOLT_CAMERA_H

#include "component.h"
#include "transform.h"

namespace Bolt {

    class Camera : public Component {
    public:
        static inline Camera* main = nullptr;
        Camera();
    };

}

#endif //BOLT_CAMERA_H
