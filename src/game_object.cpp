//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "game_object.h"
#include "window_manager.h"

using namespace Bolt;

void GameObject::update() {
    for (auto& component : components) {
        component->onUpdate();
    }
}

void GameObject::fixed() {
    for (auto& component : components) {
        component->onFixed();
    }
}

GameObject::GameObject() {
    gameObjects.insert(this);
    transform = addComponent<Transform>();
    transform->transform = transform;
}

GameObject::~GameObject() {
    gameObjects.extract(this);
}

std::unique_ptr<Component> GameObject::removeComponent(Component* to_remove) {
    auto found_iter = std::find_if(components.begin(), components.end(), [&](const auto& element){return element.get() == to_remove;});
    if (found_iter != components.end()) {
        auto extracted{std::move(*found_iter)};
        components.erase(found_iter);
        return std::move(extracted);
    } else {
        return nullptr;
    }
}

GameObject* GameObject::getChild(int index) {
    if (index < children.size())
        return static_cast<GameObject*>(children[index]);
    return nullptr;
}

std::vector<Component*> GameObject::getChildren() {
    return children;
}

GameObject::GameObject(std::string name) : GameObject() {
    this->name = name;
}

void GameObject::dispatchEvent(const Event* event) {
    auto eventHandlers_reverse = WindowManager::getEventHandlersReverse();
    for (auto& component : components) {
        if (eventHandlers_reverse[component.get()].count(event->type) == 1) {
            component->onEvent(event);
        }
    }
}

void GameObject::attachComponent(Component* component, bool isGameObject) {
    component->owner = this;
    if (isGameObject) {
        children.push_back(component);
    } else {
        component->transform = transform;
    }
    component->onAttach();
}

GameObject::GameObject(const GameObject &other) : active(other.active), name(other.name) {
    for (const auto& component : other.components) {

    }
}
