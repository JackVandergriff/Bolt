//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_FONT_H
#define BOLT_FONT_H

#include <SDL2/SDL_ttf.h>
#include <filesystem>

class Font {
private:
    TTF_Font* font;
public:
    TTF_Font* getFont();
    Font(std::filesystem::path path, int size);
    ~Font();
};


#endif //BOLT_FONT_H
