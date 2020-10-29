//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_FONT_H
#define BOLT_FONT_H

#include "filesystem_includes.h"
#include "utility.h"

struct _TTF_Font;

namespace Bolt {

    class BOLT_EXPORT Font {
    private:
        _TTF_Font* font;
    public:
        _TTF_Font* getFont();
        Font(fs::path path, int size);
        ~Font();
    };

}

#endif //BOLT_FONT_H
