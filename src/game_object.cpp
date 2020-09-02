//
// Created by jack on 8/19/20.
//

#include "game_object.h"
#include "window_manager.h"

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
}

GameObject::~GameObject() {
    gameObjects.extract(this);
}

std::unique_ptr<Component> GameObject::removeComponent(Component* to_remove) {
    for (auto& component : components) {
        if (component.get() == to_remove) {
            auto extracted = std::move(components.extract(component).value());
            extracted->Component::onAttach(nullptr);
            return std::move(extracted);
        }
    }
    return nullptr;
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
        if (eventHandlers_reverse[component.get()].contains(event->type)) {
            component->onEvent(event);
        }
    }
}
