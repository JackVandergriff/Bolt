//
// Created by jack on 8/19/20.
//

#ifndef BOLT_COMPONENT_H
#define BOLT_COMPONENT_H

#include <type_traits>
#include <concepts>
#include <SDL2/SDL.h>

#include "events.h"

class GameObject; // Forward definition, gameobject needs access to Component class

class Component {
protected:
    GameObject* owner = nullptr;
public:
    GameObject* getOwner() const;

    virtual void onAttach(GameObject* new_owner) {owner = new_owner;};
    virtual void onUpdate(){};
    virtual void onFixed(){};
    virtual void onEvent(const Event* event){};

    ~Component();
};

template<class T> concept ComponentType = std::is_base_of<Component, T>::value;

#endif //BOLT_COMPONENT_H
