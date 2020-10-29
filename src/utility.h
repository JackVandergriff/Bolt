//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_UTILITY_H
#define BOLT_UTILITY_H

#include <iostream>
#include <cmath>

#include "bolt_export.h"

struct SDL_Point;
struct SDL_Rect;

namespace Bolt {

    template<typename T>
    struct BOLT_EXPORT vec2 {
        T x{0};
        T y{0};

        vec2<T> operator+=(const vec2<T> &rhs);

        vec2<T>(T x, T y) : x(x), y(y) {}
        template<typename T2>
        vec2<T>(vec2<T2> vec): x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y)) {}
        vec2<T>() = default;
    };

    template<typename T>
    struct BOLT_EXPORT rect {
        T x{0};
        T y{0};
        T w{0};
        T h{0};

        vec2<T> getTopLeft() const;
        vec2<T> getBottomRight() const;

        rect<T> operator+=(const vec2<T> &rhs);

        template<typename T2>
        explicit operator rect<T2>() const;
        template<typename T2, class = typename std::enable_if_t<std::is_floating_point_v<T2> && std::is_integral_v<T>>>
        operator rect<T2>() const;

        rect<T>() = default;
        rect<T>(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
        rect<T>(vec2<T> top_left, T w, T h) : x(top_left.x), y(top_left.y), w(w), h(h) {}
        rect<T>(vec2<T> point_one, vec2<T> point_two) {
            x = std::min(point_one.x, point_two.x);
            y = std::min(point_one.y, point_two.y);
            w = std::max(point_one.x, point_two.x) - x;
            h = std::max(point_one.y, point_two.y) - y;
        }
    };

    struct BOLT_EXPORT rotated_rectf {
        rect<double> raw_rect;
        double rotation{0};

        vec2<double> getTopLeft() const;
        vec2<double> getBottomRight() const;

        rotated_rectf() = default;
        rotated_rectf(rect<double> rect, double rotation) : raw_rect(rect), rotation(rotation) {}
        explicit rotated_rectf(rect<double> rect) : raw_rect(rect) {}
    };

    SDL_Point sdlPointFromVec(vec2<double> vec);
    SDL_Point sdlPointFromVec(vec2<int> vec);
    rect<double> rectfFromSDL(SDL_Rect rect);
    rect<int> rectiFromSDL(SDL_Rect rect);
    SDL_Rect sdlRectFromRect(rect<double> rect);
    SDL_Rect sdlRectFromRect(rect<int> rect);

    template<typename T>
    rect<T> rect<T>::operator+=(const vec2<T> &rhs) {
        *this = *this + rhs;
        return *this;
    }

    template<typename T>
    vec2<T> rect<T>::getTopLeft() const {
        return vec2<T>{x, y};
    }

    template<typename T>
    vec2<T> rect<T>::getBottomRight() const {
        return vec2<T>{x + w, y + h};
    }

    template<typename T>
    template<typename T2>
    rect<T>::operator rect<T2>() const {
        return rect<T2>{static_cast<T2>(x), static_cast<T2>(y), static_cast<T2>(w), static_cast<T2>(h)};
    }

    template<typename T>
    template<typename T2, class>
    rect<T>::operator rect<T2>() const {
        return rect<T2>{static_cast<T2>(x), static_cast<T2>(y), static_cast<T2>(w), static_cast<T2>(h)};
    }

    template<typename T>
    vec2<T> vec2<T>::operator+=(const vec2<T> &rhs) {
        *this = *this + rhs;
        return *this;
    }

    template<typename T>
    BOLT_EXPORT vec2<T> operator+(const vec2<T> &lhs, const vec2<T> &rhs) {
        return vec2<T>{lhs.x + rhs.x, lhs.y + rhs.y};
    }

    template<typename T>
    BOLT_EXPORT vec2<T> operator*(const vec2<T> &lhs, const T &rhs) {
        return vec2<T>{lhs.x * rhs, lhs.y * rhs};
    }

    template<typename T>
    BOLT_EXPORT rect<T> operator+(const rect<T> &lhs, const vec2<T> &rhs) {
        return rect<T>{lhs.x + rhs.x, lhs.y + rhs.y, lhs.w, lhs.h};
    }

    template<typename T>
    BOLT_EXPORT rect<T> operator-(const rect<T> &lhs, const vec2<T> &rhs) {
        return rect<T>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.w, lhs.h};
    }

    template<typename T>
    BOLT_EXPORT bool inRect(const vec2<T> point, const rect<T> rect) {
        return point.x >= rect.x && point.y >= rect.y && point.x <= rect.x + rect.w && point.y <= rect.y + rect.h;
    }

    BOLT_EXPORT bool inRect(const vec2<double> point, const rotated_rectf rect);

    using vec2f = vec2<double>;
    using vec2i = vec2<int>;
    using rectf = rect<double>;
    using recti = rect<int>;

    template<typename T>
    BOLT_EXPORT std::ostream &operator<<(std::ostream &os, const vec2<T> &vec) {
        os << '(' << vec.x << ", " << vec.y << ')';
        return os;
    }

}

#define TEMPLATE_COMPONENT_TYPE_DECL "component_template_declaration_pseudo_macro.h"
#define TEMPLATE_COMPONENT_TYPE_IMPL "component_template_definition_pseudo_macro.h"

#endif //BOLT_UTILITY_H
