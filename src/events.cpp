//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "events.h"

#include <map>

using namespace Bolt;

Events Bolt::getEventFromSDL(Uint32 sdl_event) {
    static std::map<Uint32, Events> EventLookup{
            {SDL_KEYDOWN, Events::KEYBOARD},
            {SDL_KEYUP, Events::KEYBOARD},
            {SDL_MOUSEBUTTONDOWN, Events::MOUSEBUTTON},
            {SDL_MOUSEBUTTONUP, Events::MOUSEBUTTON},
            {SDL_MOUSEMOTION, Events::MOUSEMOTION},
            {SDL_MOUSEWHEEL, Events::MOUSEWHEEL}
    };

    if (EventLookup.count(sdl_event) == 1) {
        return EventLookup[sdl_event];
    }
    return Events::UNUSED;
}

Event::Event(Events type) : type(type) {}

KeyEvent::KeyEvent(SDL_KeyboardEvent sdl_event) : Event(Events::KEYBOARD),
    keyCode(sdl_event.keysym.sym),
    modifiers(sdl_event.keysym.mod),
    pressed(sdl_event.state == SDL_PRESSED),
    repeated(sdl_event.repeat) {}

MouseButtonEvent::MouseButtonEvent(SDL_MouseButtonEvent sdl_event) : Event(Events::MOUSEBUTTON),
    button(sdl_event.button),
    num_clicks(sdl_event.clicks),
    pos(sdl_event.x, sdl_event.y),
    pressed(sdl_event.state == SDL_PRESSED) {}

MouseMotionEvent::MouseMotionEvent(SDL_MouseMotionEvent sdl_event) : Event(Events::MOUSEMOTION),
    pos(sdl_event.x, sdl_event.y),
    motion(sdl_event.xrel, sdl_event.yrel) {}

MouseWheelEvent::MouseWheelEvent(SDL_MouseWheelEvent sdl_event) : Event(Events::MOUSEWHEEL),
    scroll_horizontal(sdl_event.x),
    scroll_vertical(sdl_event.y),
    normal_scroll_direction(sdl_event.direction == SDL_MOUSEWHEEL_NORMAL) {}

std::unique_ptr<Event> Bolt::translateEvent(SDL_Event event) {
    switch (getEventFromSDL(event.type)) {
        case Events::KEYBOARD:
            return std::make_unique<KeyEvent>(event.key);
        case Events::MOUSEBUTTON:
            return std::make_unique<MouseButtonEvent>(event.button);
        case Events::MOUSEMOTION:
            return std::make_unique<MouseMotionEvent>(event.motion);
        case Events::MOUSEWHEEL:
            return std::make_unique<MouseWheelEvent>(event.wheel);
        default:
            return std::make_unique<Event>(Events::UNUSED);
    }
}
