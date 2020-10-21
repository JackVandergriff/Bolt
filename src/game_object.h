//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_GAME_OBJECT_H
#define BOLT_GAME_OBJECT_H

#include <algorithm>
#include <set>
#include <vector>
#include <memory>
#include <string>
#include <type_traits>

#include "component.h"
#include "events.h"
#include "utility.h"

namespace Bolt {

    class GameObject : public CustomComponent<GameObject> {
    private:
        std::vector<std::unique_ptr<Component>> components;
        std::vector<Component*> children;
        bool active;

        void attachComponent(Component* component, bool isGameObject);
    public:
        inline static std::set<GameObject*> gameObjects;
        std::string name;

        #include TEMPLATE_COMPONENT_TYPE_DECL
        C* getComponent();
        #include TEMPLATE_COMPONENT_TYPE_DECL
        std::unique_ptr<Component> removeComponent();
        #include TEMPLATE_COMPONENT_TYPE_DECL
        C* addComponent(std::unique_ptr<Component>);

        #if __cplusplus > 201703L // C++20 support
        template<ComponentType C, class... Args>
        C* addComponent(Args &&...);
        #else // stuck on C++17
        template<typename C, class... Args, class = typename std::enable_if<std::is_base_of<Component, C>::value>::type> C* addComponent(Args&&...);
        #endif
        std::unique_ptr<Component> removeComponent(Component*);

        void update();
        void fixed();
        void dispatchEvent(const Event*);

        GameObject* getChild(int);
        std::vector<Component*> getChildren();

        GameObject();
        GameObject(std::string);
        GameObject(const GameObject& other);
        GameObject& operator=(const GameObject& other);
        GameObject(GameObject&&) = delete;
        GameObject& operator=(GameObject&&) = delete;
        ~GameObject();
    };

    #include TEMPLATE_COMPONENT_TYPE_IMPL
    C* GameObject::getComponent() {
        for (const auto &component : components) {
            if (auto casted = dynamic_cast<C*>(component.get())) {
                return casted;
            }
        }
        return nullptr;
    }

    #include TEMPLATE_COMPONENT_TYPE_IMPL
    std::unique_ptr<Component> GameObject::removeComponent() {
        auto found_iter = std::find_if(components.begin(), components.end(), [](const auto& element){return dynamic_cast<C*>(element.get()) != nullptr;});
        if (found_iter != components.end()) {
            auto extracted{std::move(*found_iter)};
            components.erase(found_iter);
            return std::move(extracted);
        } else {
            return nullptr;
        }
    }

    #if __cplusplus > 201703L // C++20 support
    template<ComponentType C, class... Args>
    #else // stuck on C++17
    template<typename C, class... Args, class>
    #endif
    C* GameObject::addComponent(Args &&... args) {
        constexpr bool isGameObject = std::is_same_v<C, GameObject>;
        std::unique_ptr<Component> component = std::make_unique<C>(std::forward<Args>(args)...);

        attachComponent(component.get(), isGameObject);

        auto to_return = static_cast<C*>(component.get());
        components.push_back(std::move(component));
        return to_return;
    }

    #include TEMPLATE_COMPONENT_TYPE_IMPL
    C* GameObject::addComponent(std::unique_ptr<Component> component) {
        constexpr bool isGameObject = std::is_same_v<C, GameObject>;
        attachComponent(component.get(), isGameObject);

        C* to_return = dynamic_cast<C*>(component.get());
        if (to_return == nullptr)
            throw std::bad_cast();

        components.push_back(std::move(component));
        return to_return;
    }

}

#endif //BOLT_GAME_OBJECT_H