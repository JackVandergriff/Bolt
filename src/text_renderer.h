//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_TEXT_RENDERER_H
#define BOLT_TEXT_RENDERER_H

#include "text.h"
#include "transform.h"
#include "game_object.h"

namespace Bolt {

    class BOLT_EXPORT TextRenderer : public CustomComponent<TextRenderer> {
    public:
        Text text;

        void onUpdate() override;
    };

}

#endif //BOLT_TEXT_RENDERER_H
