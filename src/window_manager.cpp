//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "window_manager.h"
#include "game_object.h"
#include "camera.h"

#include <iostream>

#include <chipmunk/chipmunk.h>

using namespace Bolt;

WindowManager::WindowManager(std::string title) {
    cpSpace* test = cpSpaceNew();
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    singleton = this;
    flush();
    cpSpaceFree(test);
}

WindowManager::WindowManager() {
    WindowManager("bolt");
}

WindowManager::~WindowManager() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

std::shared_ptr<Texture> WindowManager::loadTexture(fs::path path) {
    SDL_Surface* textureSurface = IMG_Load(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(singleton->renderer, textureSurface);
    SDL_FreeSurface(textureSurface);

    return std::make_shared<Texture>(texture);
}

void WindowManager::render(Renderable to_render) {
    const static SDL_Point center{0,0};

    if (!to_render.screenSpace)
        to_render.dest = applyGeometry(to_render.dest, Camera::main->getOwner()->getComponent<Transform>()->globalGeometry());

    SDL_Rect source = (SDL_Rect)to_render.source;
    SDL_Rect dest = (SDL_Rect)to_render.dest.raw_rect;
    SDL_RenderCopyEx(
            singleton->renderer,
            to_render.texture,
            &source,
            &dest,
            to_render.dest.rotation,
            &center,
            SDL_FLIP_NONE);
}

void WindowManager::flush() {
    SDL_RenderPresent(singleton->renderer);
    SDL_RenderClear(singleton->renderer);
}

void WindowManager::run() {
    SDL_Event sdl_event;
    while (sdl_event.type != SDL_QUIT) {
        while (SDL_PollEvent(&sdl_event) != 0) {
            if (sdl_event.type == SDL_QUIT) {
                break;
            } else if (sdl_event.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&(singleton->mouse_position.x), &(singleton->mouse_position.y));
            }

            std::unique_ptr<Event> event = translateEvent(sdl_event);

            for (auto& component : eventHandlers[event->type]) {
                component->onEvent(event.get());
            }
        }

        for (auto& gameObject : GameObject::gameObjects) {
            gameObject->update();
        }
        flush();
        SDL_Delay(16);
    }
}

void WindowManager::registerHandler(Component* component, Events event_type) {
    eventHandlers[event_type].insert(component);
    eventHandlers_reverse[component].insert(event_type);
}

void WindowManager::unregisterHandler(Component* component, Events event_type) {
    if (eventHandlers[event_type].count(component) == 0) {
        return;
    }

    eventHandlers[event_type].erase(component);
    eventHandlers_reverse[component].erase(event_type);
}

void WindowManager::unregisterHandler(Component* component) {
    if (eventHandlers_reverse.count(component) == 0) {
        return;
    }

    for (auto event_type : eventHandlers_reverse[component]) {
        eventHandlers[event_type].erase(component);
    }

    eventHandlers_reverse.erase(component);
}

const std::map<Events, std::set<Component*>>& WindowManager::getEventHandlers() {
    return eventHandlers;
}

const std::map<Component*, std::set<Events>>& WindowManager::getEventHandlersReverse() {
    return eventHandlers_reverse;
}

vec2f WindowManager::getMousePos(bool screenSpace) {
    if (screenSpace)
        return (vec2f)singleton->mouse_position;
    return stripGeometry((vec2f)singleton->mouse_position, Camera::main->getOwner()->getComponent<Transform>()->globalGeometry());
}

std::shared_ptr<Texture> WindowManager::createTextureFromSurface(SDL_Surface* surface) {
    return std::make_shared<Texture>(SDL_CreateTextureFromSurface(singleton->renderer, surface));
}
