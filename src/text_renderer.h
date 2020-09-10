//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_TEXT_RENDERER_H
#define BOLT_TEXT_RENDERER_H

#include "text.h"
#include "transform.h"
#include "game_object.h"

namespace Bolt {

    class TextRenderer : public Component {
    private:
        Transform* transform;
    public:
        Text text;

        void onAttach() override;
        void onUpdate() override;
    };

}

#endif //BOLT_TEXT_RENDERER_H
