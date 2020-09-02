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

#include "component.h"
#include "events.h"

class GameObject : public Component{
private:
    std::set<std::unique_ptr<Component>> components;
    std::vector<Component*> children;
    bool active;
public:
    inline static std::set<GameObject*> gameObjects;
    std::string name;

    template<ComponentType C> C* getComponent();
    template<ComponentType C> std::unique_ptr<Component> removeComponent();
    std::unique_ptr<Component> removeComponent(Component*);
    template<ComponentType C, class... Args> C* addComponent(Args&&...);
    template<ComponentType C> C* addComponent(std::unique_ptr<Component>);

    void update();
    void fixed();
    void dispatchEvent(const Event*);

    GameObject* getChild(int);
    std::vector<Component*> getChildren();

    GameObject();
    GameObject(std::string);
    ~GameObject();
};

template<ComponentType C>
C* GameObject::getComponent() {
    for (const auto& component : components) {
        if (auto casted = dynamic_cast<C*>(component.get())) {
            return casted;
        }
    }
    return nullptr;
}

template<ComponentType C>
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

template<ComponentType C, class... Args>
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

template<ComponentType C>
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