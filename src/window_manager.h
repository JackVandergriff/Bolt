//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_WINDOW_MANAGER_H
#define BOLT_WINDOW_MANAGER_H

#include "texture.h"
#include "sprite_renderer.h"
#include "events.h"
#include "filesystem_includes.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include <map>
#include <set>
#include <string>
#include <functional>

namespace Bolt {

    struct Renderable {
        SDL_Texture* texture;
        rectf source;
        rotated_rectf dest;
        bool screenSpace{false};
    };

    class WindowManager {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        GameObject dummy_obj;

        vec2i mouse_position;
        inline static WindowManager* singleton;
        inline static std::map<Events, std::set<Component*>> eventHandlers;
        inline static std::map<Component*, std::set<Events>> eventHandlers_reverse;
    public:
        WindowManager(std::string);
        WindowManager();
        ~WindowManager();

        inline static GameObject* dummy;

        static std::shared_ptr<Texture> loadTexture(fs::path);
        static vec2f getMousePos(bool screenSpace = false);
        static std::shared_ptr<Texture> createTextureFromSurface(SDL_Surface* surface);
        static void render(Renderable to_render);
        static void flush();
        static void run(std::function<void()> update=[](){});
        static void registerHandler(Component*, Events);
        static void unregisterHandler(Component*, Events);
        static void unregisterHandler(Component*);
        static const std::map<Events, std::set<Component*>> &getEventHandlers();
        static const std::map<Component*, std::set<Events>> &getEventHandlersReverse();

        //Delete other Rule of Six functions (No copying or moving)
        WindowManager(const WindowManager &) = delete;
        WindowManager &operator=(const WindowManager &) = delete;
        WindowManager(WindowManager &&) noexcept = delete;
        WindowManager &operator=(WindowManager &&) noexcept = delete;
    };

}

#endif //BOLT_WINDOW_MANAGER_H
