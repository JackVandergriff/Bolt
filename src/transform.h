//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_TRANSFORM_H
#define BOLT_TRANSFORM_H

#include "component.h"
#include "game_object.h"
#include "geometry.h"
#include "utility.h"

namespace Bolt {

    class Transform : public Component {
    public:
        Geometry local_geometry;
        Geometry globalGeometry() const;
    };

}

#endif //BOLT_TRANSFORM_H