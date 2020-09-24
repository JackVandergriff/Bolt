//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "geometry.h"
#include <assert.h>
#include <cmath>

using namespace Bolt;

Geometry::Geometry(vec2f offset, double rotation, double scale): offset(offset), rotation(rotation), scale(scale) {
    updateCache();
}

void Geometry::updateCache() const {
    rot_cache = rotation;
    cos = std::cos(rotation * M_PI / 180.f);
    sin = std::sin(rotation * M_PI / 180.f);
}

Geometry Bolt::applyGeometry(const Geometry& external_geometry, const Geometry& to_apply) {
    if (to_apply.rotation != to_apply.rot_cache) to_apply.updateCache();
    double x = external_geometry.offset.x; // would double& be better optimized?? idk
    double y = external_geometry.offset.y;
    double x1 = to_apply.offset.x;
    double y1 = to_apply.offset.y;
    return Geometry(
            {((x - x1) * to_apply.cos + (y - y1) * to_apply.sin) / to_apply.scale, (-(x - x1) * to_apply.sin + (y - y1) * to_apply.cos) / to_apply.scale},
            external_geometry.rotation - to_apply.rotation,
            external_geometry.scale / to_apply.scale);
}

Geometry Bolt::stripGeometry(const Geometry& local_geometry, const Geometry& to_strip) {
    if (to_strip.rotation != to_strip.rot_cache) to_strip.updateCache();
    double x = local_geometry.offset.x; // would double& be better optimized?? idk
    double y = local_geometry.offset.y;
    double x1 = to_strip.offset.x;
    double y1 = to_strip.offset.y;
    return Geometry(
            {to_strip.scale * (x * to_strip.cos - y * to_strip.sin) + x1, to_strip.scale * (y * to_strip.cos + x * to_strip.sin) + y1},
            local_geometry.rotation + to_strip.rotation,
            local_geometry.scale * to_strip.scale);
}

vec2f Bolt::applyGeometry(const vec2f& external_vec2f, const Geometry& to_apply) {
    return applyGeometry(Geometry{external_vec2f, 0, 1}, to_apply).offset;
}

vec2f Bolt::stripGeometry(const vec2f& local_vec2f, const Geometry& to_strip) {
    return stripGeometry(Geometry{local_vec2f, 0, 1}, to_strip).offset;
}

rotated_rectf Bolt::applyGeometry(const rectf& external_rect, const Geometry& to_apply) {
    return rotated_rectf{{applyGeometry(external_rect.getTopLeft(), to_apply), external_rect.w / to_apply.scale ,external_rect.h / to_apply.scale}, -to_apply.rotation};
}

rotated_rectf Bolt::stripGeometry(const rectf& local_rect, const Geometry& to_strip) {
    return rotated_rectf{{stripGeometry(local_rect.getTopLeft(), to_strip), local_rect.w * to_strip.scale , local_rect.h * to_strip.scale}, to_strip.rotation};
}

std::ostream& operator<<(std::ostream& os, const Geometry& geometry) {
    return os << "geometry: ( at " << geometry.offset << ", angled " << geometry.rotation << " degrees, scaled " << geometry.scale << " times)";
}

rotated_rectf Bolt::applyGeometry(const rotated_rectf &external_rect, const Geometry &to_apply) {
    return rotated_rectf{
        {applyGeometry(external_rect.getTopLeft(), to_apply),
        external_rect.raw_rect.w / to_apply.scale ,
        external_rect.raw_rect.h / to_apply.scale},
        external_rect.rotation - to_apply.rotation};
}

rotated_rectf Bolt::stripGeometry(const rotated_rectf &local_rect, const Geometry &to_strip) {
    return rotated_rectf{
        {stripGeometry(local_rect.getTopLeft(), to_strip),
         local_rect.raw_rect.w * to_strip.scale ,
         local_rect.raw_rect.h * to_strip.scale},
         local_rect.rotation + to_strip.rotation};
}
