//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "text.h"
#include "window_manager.h"

void Text::renderText() {
    SDL_Surface* textSurface = TTF_RenderText_Blended(font->getFont(), text.c_str(), SDL_Color{255, 255, 255, 255});
    rendered_text = WindowManager::createTextureFromSurface(textSurface);
    dimensions.x = textSurface->w;
    dimensions.y = textSurface->h;
    SDL_FreeSurface(textSurface);
}

std::shared_ptr<Font> Text::getFont() const {
    return font;
}

void Text::setFont(std::shared_ptr<Font> font) {
    this->font = font;
    renderText();
}

std::string Text::getText() const {
    return text;
}

void Text::setText(std::string text) {
    this->text = text;
    renderText();
}

SDL_Texture* Text::getRenderedText() const {
    return rendered_text.get()->getTexture();
}

vec2f Text::getDimensions() const {
    return dimensions;
}

Text::Text(std::shared_ptr<Font> font, std::string text) : font(font), text(text) {
    renderText();
}
