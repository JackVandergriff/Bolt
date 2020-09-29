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
        Geometry externalGeometry() const;
        void setGlobalGeometry(Geometry global_geometry);

        auto globalToLocal(auto global) {
            return applyGeometry(global, globalGeometry());
        };

        auto localToGlobal(auto local) {
            return stripGeometry(local, globalGeometry());
        };

        auto globalToExternal(auto global) {
            return applyGeometry(global, externalGeometry());
        };

        auto externalToGlobal(auto external) {
            return stripGeometry(external, externalGeometry());
        };

        auto localToExternal(auto local) {
            return stripGeometry(local, local_geometry);
        };

        auto externalToLocal(auto external) {
            return applyGeometry(external, local_geometry);
        };
    };

}

#endif //BOLT_TRANSFORM_H