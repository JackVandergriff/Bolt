//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_COMPONENT_H
#define BOLT_COMPONENT_H

#include <type_traits>
#if __cplusplus > 201703L
#include <concepts>
#endif
#include <SDL.h>

#include "events.h"

namespace Bolt {

    class GameObject; // Forward definition, gameobject needs access to Component class
    class Transform;

    class Component {
    protected:
        GameObject* owner = nullptr;
        Transform* transform = nullptr;
    public:
        GameObject* getOwner() const;
        Transform* getTransform() const;

        virtual void onAttach() {};
        virtual void onUpdate() {};
        virtual void onFixed() {};
        virtual void onEvent(const Event* event) {};

        friend class GameObject;

        ~Component();
    };

#if __cplusplus > 201703L // C++20 support
    template<class T> concept ComponentType = std::is_base_of<Component, T>::value;
#endif

}

#endif //BOLT_COMPONENT_H
