//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_GEOMETRY_H
#define BOLT_GEOMETRY_H

#include "utility.h"

#include <iostream>

namespace Bolt {

    struct Geometry {
        vec2f offset{0, 0};
        float rotation{0};
        float scale{1};

        Geometry() = default;
        Geometry(vec2f offset, float rotation, float scale);

        friend Geometry applyGeometry(const Geometry &external_geometry, const Geometry &to_apply);
        friend vec2f applyGeometry(const vec2f &external_vec2f, const Geometry &to_apply);
        friend rotated_rectf applyGeometry(const rectf &external_rect, const Geometry &to_apply);
        friend Geometry stripGeometry(const Geometry &local_geometry, const Geometry &to_strip);
        friend vec2f stripGeometry(const vec2f &local_vec2f, const Geometry &to_strip);
        friend rotated_rectf stripGeometry(const rectf &local_rect, const Geometry &to_strip);

    private:
        mutable float rot_cache{0};
        mutable float cos{1};
        mutable float sin{0};
        void updateCache() const;
    };

    Geometry applyGeometry(const Geometry &external_geometry, const Geometry &to_apply);
    vec2f applyGeometry(const vec2f &external_vec2f, const Geometry &to_apply);
    rotated_rectf applyGeometry(const rectf &external_rect, const Geometry &to_apply);
    rotated_rectf applyGeometry(const rotated_rectf &external_rect, const Geometry &to_apply);
    Geometry stripGeometry(const Geometry &local_geometry, const Geometry &to_strip);
    vec2f stripGeometry(const vec2f &local_vec2f, const Geometry &to_strip);
    rotated_rectf stripGeometry(const rectf &local_rect, const Geometry &to_strip);
    rotated_rectf stripGeometry(const rotated_rectf &local_rect, const Geometry &to_strip);

}

std::ostream &operator<<(std::ostream &os, const Bolt::Geometry &geometry);

#endif //BOLT_GEOMETRY_H
