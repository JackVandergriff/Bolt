//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_FONT_H
#define BOLT_FONT_H

#include <SDL_ttf.h>
#include "filesystem_includes.h"

class Font {
private:
    TTF_Font* font;
public:
    TTF_Font* getFont();
    Font(fs::path path, int size);
    ~Font();
};


#endif //BOLT_FONT_H
