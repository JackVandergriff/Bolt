//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_GEOMETRY_H
#define BOLT_GEOMETRY_H

#include "utility.h"

#include <iostream>

namespace Bolt {

    struct BOLT_EXPORT Geometry {
        vec2f offset{0, 0};
        double rotation{0};
        double scale{1};

        Geometry() = default;
        Geometry(vec2f offset, double rotation, double scale);

        friend Geometry applyGeometry(const Geometry &external_geometry, const Geometry &to_apply);
        friend vec2f applyGeometry(const vec2f &external_vec2f, const Geometry &to_apply);
        friend rotated_rectf applyGeometry(const rectf &external_rect, const Geometry &to_apply);
        friend Geometry stripGeometry(const Geometry &local_geometry, const Geometry &to_strip);
        friend vec2f stripGeometry(const vec2f &local_vec2f, const Geometry &to_strip);
        friend rotated_rectf stripGeometry(const rectf &local_rect, const Geometry &to_strip);

    private:
        mutable double rot_cache{0};
        mutable double cos{1};
        mutable double sin{0};
        void updateCache() const;
    };

    BOLT_EXPORT Geometry applyGeometry(const Geometry &external_geometry, const Geometry &to_apply);
    BOLT_EXPORT vec2f applyGeometry(const vec2f &external_vec2f, const Geometry &to_apply);
    BOLT_EXPORT rotated_rectf applyGeometry(const rectf &external_rect, const Geometry &to_apply);
    BOLT_EXPORT rotated_rectf applyGeometry(const rotated_rectf &external_rect, const Geometry &to_apply);
    BOLT_EXPORT Geometry stripGeometry(const Geometry &local_geometry, const Geometry &to_strip);
    BOLT_EXPORT vec2f stripGeometry(const vec2f &local_vec2f, const Geometry &to_strip);
    BOLT_EXPORT rotated_rectf stripGeometry(const rectf &local_rect, const Geometry &to_strip);
    BOLT_EXPORT rotated_rectf stripGeometry(const rotated_rectf &local_rect, const Geometry &to_strip);

}

BOLT_EXPORT std::ostream &operator<<(std::ostream &os, const Bolt::Geometry &geometry);

#endif //BOLT_GEOMETRY_H
