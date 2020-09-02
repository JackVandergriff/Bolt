//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "collider.h"
#include "transform.h"
#include "window_manager.h"

Collider::Collider() {
    WindowManager::registerHandler(this, Events::MOUSEBUTTON);
}

void Collider::onEvent(const Event* event) {
    if (event->type == Events::MOUSEBUTTON) {
        auto e = dynamic_cast<const MouseButtonEvent*>(event);
        if (isInside({(float)(e->pos.x), (float)(e->pos.y)})) {

        }
    }
}

void Collider::onAttach(GameObject* owner) {
    transform = owner->getComponent<Transform>();
}

bool Collider::isInside(vec2f global_position) {
    return inRect(applyGeometry(global_position, transform->globalGeometry()), collision);
}
