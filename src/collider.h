//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_COLLIDER_H
#define BOLT_COLLIDER_H

#include "component.h"

namespace Bolt {

    class BOLT_EXPORT Collider : public CustomComponent<Collider> {
    public:
        virtual bool isInside(vec2f global_point) {return false;};
    };

}

#endif //BOLT_COLLIDER_H
