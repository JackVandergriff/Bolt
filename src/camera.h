//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_CAMERA_H
#define BOLT_CAMERA_H

#include "component.h"
#include "transform.h"

class Camera : public Component {
private:
    Transform* transform;
public:
    static inline Camera* main = nullptr;
    void onAttach() override;
    Camera();
};


#endif //BOLT_CAMERA_H
