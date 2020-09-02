//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "text_renderer.h"
#include "window_manager.h"

void TextRenderer::onAttach(GameObject* g) {
    transform = owner->getComponent<Transform>();
}

void TextRenderer::onUpdate() {
    rectf source = {{0, 0}, text.getDimensions()};
    WindowManager::render(Renderable{text.getRenderedText(), source, stripGeometry(source, transform->globalGeometry()), true});
}
