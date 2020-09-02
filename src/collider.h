//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_COLLIDER_H
#define BOLT_COLLIDER_H

#include "component.h"
#include "transform.h"

class Collider : public Component {
private:
    Transform* transform;
public:
    rectf collision;
    void onEvent(const Event* event) override;
    void onAttach(GameObject* owner) override;
    bool isInside(vec2f);

    Collider();
};


#endif //BOLT_COLLIDER_H
