//
// Created by jack on 8/19/20.
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

class GameObject : public Component{
private:
    std::set<std::unique_ptr<Component>> components;
    std::vector<Component*> children;
    bool active;
public:
    inline static std::set<GameObject*> gameObjects;
    std::string name;

#include TEMPLATE_COMPONENT_TYPE
    C* getComponent();
#include TEMPLATE_COMPONENT_TYPE
    std::unique_ptr<Component> removeComponent();
#include TEMPLATE_COMPONENT_TYPE
    C* addComponent(std::unique_ptr<Component>);

#if __cplusplus > 201703L // C++20 support
    template<ComponentType C, class... Args> C* addComponent(Args&&...);
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
    ~GameObject();
};

#include TEMPLATE_COMPONENT_TYPE
C* GameObject::getComponent() {
    for (const auto& component : components) {
        if (auto casted = dynamic_cast<C*>(component.get())) {
            return casted;
        }
    }
    return nullptr;
}

#include TEMPLATE_COMPONENT_TYPE
std::unique_ptr<Component> GameObject::removeComponent() {
    for (const auto& component : components) {
        if (dynamic_cast<C*>(component.get())) {
            auto extracted = std::move(components.extract(component).value());
            extracted->Component::onAttach(nullptr);
            if (std::is_same<C, GameObject>::value) {
                children.erase(std::find(children.begin(), children.end(), extracted.get()));
            }
            return std::move(extracted);
        }
    }
    return nullptr;
}

#if __cplusplus > 201703L // C++20 support
template<ComponentType C, class... Args>
#else // stuck on C++17
template<typename C, class... Args, class = typename std::enable_if<std::is_base_of<Component, C>::value>::type>
#endif
C* GameObject::addComponent(Args&&... args) {
    std::unique_ptr<Component> comp = std::make_unique<C>(std::forward<Args>(args)...);
    if (std::is_same<C, GameObject>::value) {
        children.push_back(comp.get());
    }
    comp->Component::onAttach(this);
    comp->onAttach(this);
    auto to_return = static_cast<C*>(comp.get());
    components.insert(std::move(comp));
    return to_return;
}

#include TEMPLATE_COMPONENT_TYPE
C* GameObject::addComponent(std::unique_ptr<Component> component) {
    if (std::is_same<C, GameObject>::value) {
        children.push_back(component.get());
    }

    C* to_return = dynamic_cast<C*>(component.get());
    if (to_return == nullptr)
        throw std::bad_cast();

    component->onAttach(this);
    components.insert(std::move(component));
    return to_return;
}

#endif //BOLT_GAME_OBJECT_H