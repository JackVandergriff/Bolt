//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "utility.h"
#include "geometry.h"

bool inRect(const vec2<float> point, const rotated_rectf rect) {
    return inRect(applyGeometry(point, Geometry{rect.getTopLeft(), rect.rotation, 1}), rect.raw_rect);
}

vec2<float> rotated_rectf::getTopLeft() const {
    return raw_rect.getTopLeft();
}

vec2<float> rotated_rectf::getBottomRight() const {
    float sin = std::sin(rotation * M_PI / 180.f);
    float cos = std::cos(rotation * M_PI / 180.f);
    return vec2<float>{raw_rect.x + cos * raw_rect.w + sin * raw_rect.h, raw_rect.y + cos * raw_rect.h - sin * raw_rect.w};
}
