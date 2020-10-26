//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_CAMERA_H
#define BOLT_CAMERA_H

#include "component.h"
#include "transform.h"

namespace Bolt {

    class Camera : public CustomComponent<Camera> {
    public:
        static inline Camera* main = nullptr;
        void onInit() override;
    };

}

#endif //BOLT_CAMERA_H
