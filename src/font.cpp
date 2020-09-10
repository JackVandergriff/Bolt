//
// Copyright (c) 2020 Jack Vandergriff.
//

#include "font.h"

TTF_Font* Font::getFont() {
    return font;
}

Font::Font(fs::path path, int size) {
    font = TTF_OpenFont(path.c_str(), size);
}

Font::~Font() {
    if (font) TTF_CloseFont(font);
}
