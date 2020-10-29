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
#include <memory>

#include "events.h"

namespace Bolt {

    class GameObject; // Forward definition, gameobject needs access to Component class
    class Transform;

    class BOLT_EXPORT Component {
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
        virtual void onInit() {};
        virtual std::unique_ptr<Component> clone() const=0;

        friend class GameObject;

        virtual ~Component();
    };

    template<typename T>
    class BOLT_EXPORT CustomComponent : public Component {
        std::unique_ptr<Component> clone() const override {
            auto to_return =  std::make_unique<T>(static_cast<const T&>(*this));
            to_return.get()->onInit();
            return to_return;
        }
    };

#if __cplusplus > 201703L // C++20 support
    template<class T> concept ComponentType = std::is_base_of<Component, T>::value;
#endif

}

#endif //BOLT_COMPONENT_H
