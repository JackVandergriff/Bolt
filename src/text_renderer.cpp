//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "text_renderer.h"
#include "window_manager.h"

using namespace Bolt;

void TextRenderer::onUpdate() {
    rectf source = {{0, 0}, text.getDimensions()};
    WindowManager::render(Renderable{text.getRenderedText(), source, transform->localToGlobal(source), true});
}
