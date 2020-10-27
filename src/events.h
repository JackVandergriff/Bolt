//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_EVENTS_H
#define BOLT_EVENTS_H

#include <SDL.h>
#include <memory>

#include "utility.h"

namespace Bolt {

    enum class Events {
        UNUSED, KEYBOARD, MOUSEBUTTON, MOUSEMOTION, MOUSEWHEEL, COLLISION
        //KEYDOWN, KEYUP, MOUSEDOWN, MOUSEUP, MOUSEMOVE, MOUSEWHEEL, UNUSED, COLLISION
    };

    struct Event {
    protected:
        virtual void wow_this_is_polymorphic_see() {};
    public:
        const Events type{Events::UNUSED};
        Event(Events type);
        Event() = default;
    };

    struct KeyEvent : public Event {
    public:
        uint keyCode;
        uint16_t modifiers;
        bool pressed;
        bool repeated;

        KeyEvent(SDL_KeyboardEvent sdl_event);
    };

    struct MouseButtonEvent : public Event {
        uint8_t button;
        uint8_t num_clicks;
        vec2<int32_t> pos;
        bool pressed;

        MouseButtonEvent(SDL_MouseButtonEvent sdl_event);
    };

    struct MouseMotionEvent : public Event {
        vec2<int32_t> pos;
        vec2<int32_t> motion;

        MouseMotionEvent(SDL_MouseMotionEvent sdl_event);
    };

    struct MouseWheelEvent : public Event {
        int32_t scroll_horizontal;
        int32_t scroll_vertical;
        bool normal_scroll_direction;

        MouseWheelEvent(SDL_MouseWheelEvent sdl_event);
    };

    Events getEventFromSDL(Uint32 sdl_event);

    std::unique_ptr<Event> translateEvent(SDL_Event event);

}

#endif //BOLT_EVENTS_H
