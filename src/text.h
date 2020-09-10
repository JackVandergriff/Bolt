//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_TEXT_H
#define BOLT_TEXT_H

#include <SDL_ttf.h>
#include <memory>
#include <string>

#include "texture.h"
#include "font.h"
#include "utility.h"

namespace Bolt {

    class Text {
    private:
        std::shared_ptr<Texture> rendered_text;
        vec2f dimensions;
        std::shared_ptr<Font> font;
        std::string text;

        void renderText();
    public:
        Text() = default;
        Text(std::shared_ptr<Font> font, std::string text);
        std::shared_ptr<Font> getFont() const;
        void setFont(std::shared_ptr<Font> font);
        std::string getText() const;
        void setText(std::string text);
        SDL_Texture* getRenderedText() const;
        vec2f getDimensions() const;
    };

}

#endif //BOLT_TEXT_H
