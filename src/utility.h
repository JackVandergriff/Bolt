//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_UTILITY_H
#define BOLT_UTILITY_H

#include <iostream>
#include <cmath>
#include <SDL.h>

namespace Bolt {

    template<typename T>
    struct vec2 {
        T x{0};
        T y{0};

        vec2<T> operator+=(const vec2<T> &rhs);

        explicit operator SDL_Point() const;

        vec2<T>(T x, T y) : x(x), y(y) {}
        template<typename T2>
        vec2<T>(vec2<T2> vec): x((T) vec.x), y((T) vec.y) {}
        vec2<T>() = default;
    };

    template<typename T>
    struct rect {
        T x{0};
        T y{0};
        T w{0};
        T h{0};

        vec2<T> getTopLeft() const;
        vec2<T> getBottomRight() const;

        rect<T> operator+=(const vec2<T> &rhs);

        template<typename T2>
        explicit operator rect<T2>() const;
        explicit operator SDL_Rect() const;

        rect<T>() = default;
        rect<T>(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
        rect<T>(vec2<T> top_left, T w, T h) : x(top_left.x), y(top_left.y), w(w), h(h) {}
        rect<T>(SDL_Rect sdl_rect) : x((T) sdl_rect.x), y((T) sdl_rect.y), w((T) sdl_rect.w), h((T) sdl_rect.h) {}
        rect<T>(vec2<T> point_one, vec2<T> point_two) {
            x = std::min(point_one.x, point_two.x);
            y = std::min(point_one.y, point_two.y);
            w = std::max(point_one.x, point_two.x) - x;
            h = std::max(point_one.y, point_two.y) - y;
        }
    };

    struct rotated_rectf {
        rect<float> raw_rect;
        float rotation{0};

        vec2<float> getTopLeft() const;
        vec2<float> getBottomRight() const;

        rotated_rectf() = default;
        rotated_rectf(rect<float> rect, float rotation) : raw_rect(rect), rotation(rotation) {}
        explicit rotated_rectf(rect<float> rect) : raw_rect(rect) {}
    };

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
    rect<T>::operator SDL_Rect() const {
        return SDL_Rect{(int) x, (int) y, (int) w, (int) h};
    }

    template<typename T>
    vec2<T> vec2<T>::operator+=(const vec2<T> &rhs) {
        *this = *this + rhs;
        return *this;
    }

    template<typename T>
    vec2<T>::operator SDL_Point() const {
        return SDL_Point{(int) x, (int) y};
    }

    template<typename T>
    vec2<T> operator+(const vec2<T> &lhs, const vec2<T> &rhs) {
        return vec2<T>{lhs.x + rhs.x, lhs.y + rhs.y};
    }

    template<typename T>
    vec2<T> operator*(const vec2<T> &lhs, const T &rhs) {
        return vec2<T>{lhs.x * rhs, lhs.y * rhs};
    }

    template<typename T>
    rect<T> operator+(const rect<T> &lhs, const vec2<T> &rhs) {
        return rect<T>{lhs.x + rhs.x, lhs.y + rhs.y, lhs.w, lhs.h};
    }

    template<typename T>
    rect<T> operator-(const rect<T> &lhs, const vec2<T> &rhs) {
        return rect<T>{lhs.x - rhs.x, lhs.y - rhs.y, lhs.w, lhs.h};
    }

    template<typename T>
    bool inRect(const vec2<T> point, const rect<T> rect) {
        return point.x >= rect.x && point.y >= rect.y && point.x <= rect.x + rect.w && point.y <= rect.y + rect.h;
    }

    bool inRect(const vec2<float> point, const rotated_rectf rect);

    using vec2f = vec2<float>;
    using vec2i = vec2<int>;
    using rectf = rect<float>;
    using recti = rect<int>;

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const vec2<T> &vec) {
        os << '(' << vec.x << ", " << vec.y << ')';
        return os;
    }

}

#define TEMPLATE_COMPONENT_TYPE_DECL "component_template_declaration_pseudo_macro.h"
#define TEMPLATE_COMPONENT_TYPE_IMPL "component_template_definition_pseudo_macro.h"

#endif //BOLT_UTILITY_H
