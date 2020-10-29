//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "utility.h"
#include "geometry.h"
#include <SDL.h>

using namespace Bolt;

bool Bolt::inRect(const vec2<double> point, const rotated_rectf rect) {
    return inRect(applyGeometry(point, Geometry{rect.getTopLeft(), rect.rotation, 1}), rect.raw_rect);
}

SDL_Rect Bolt::sdlRectFromRect(rect<int> rect) {
    return SDL_Rect{rect.x, rect.y, rect.w, rect.h};
}

SDL_Rect Bolt::sdlRectFromRect(rect<double> rect) {
    return SDL_Rect{(int)rect.x, (int)rect.y, (int)rect.w, (int)rect.h};
}

rect<int> Bolt::rectiFromSDL(SDL_Rect rect) {
    return recti{rect.x, rect.y, rect.w, rect.h};
}

rect<double> Bolt::rectfFromSDL(SDL_Rect rect) {
    return rectf{(double)rect.x, (double)rect.y, (double)rect.w, (double)rect.h};
}

SDL_Point Bolt::sdlPointFromVec(vec2<int> vec) {
    return SDL_Point{vec.x, vec.y};
}

SDL_Point Bolt::sdlPointFromVec(vec2<double> vec) {
    return SDL_Point{(int)vec.x, (int)vec.y};
}

vec2<double> rotated_rectf::getTopLeft() const {
    return raw_rect.getTopLeft();
}

vec2<double> rotated_rectf::getBottomRight() const {
    double sin = std::sin(rotation * M_PI / 180.f);
    double cos = std::cos(rotation * M_PI / 180.f);
    return vec2f{raw_rect.x + cos * raw_rect.w + sin * raw_rect.h, raw_rect.y + cos * raw_rect.h - sin * raw_rect.w};
}
