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

    class Transform : public CustomComponent<Transform> {
    public:
        Geometry local_geometry;
        Geometry globalGeometry() const;
        Geometry externalGeometry() const;
        void setGlobalGeometry(Geometry global_geometry);

        template<typename T>
        auto globalToLocal(T global) {
            return applyGeometry(global, globalGeometry());
        };

        template<typename T>
        auto localToGlobal(T local) {
            return stripGeometry(local, globalGeometry());
        };

        template<typename T>
        auto globalToExternal(T global) {
            return applyGeometry(global, externalGeometry());
        };

        template<typename T>
        auto externalToGlobal(T external) {
            return stripGeometry(external, externalGeometry());
        };

        template<typename T>
        auto localToExternal(T local) {
            return stripGeometry(local, local_geometry);
        };

        template<typename T>
        auto externalToLocal(T external) {
            return applyGeometry(external, local_geometry);
        };
    };

}

#endif //BOLT_TRANSFORM_H