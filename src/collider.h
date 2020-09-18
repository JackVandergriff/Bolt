//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_COLLIDER_H
#define BOLT_COLLIDER_H

#include "component.h"

namespace Bolt {

    class Collider : public Component {
    public:
        virtual bool isInside(vec2f) = 0;
    };

}

#endif //BOLT_COLLIDER_H
