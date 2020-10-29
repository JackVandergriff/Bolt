//
// Copyright (c) 2020 Jack Vandergriff.
//

#ifndef BOLT_TEXTURE_H
#define BOLT_TEXTURE_H

#include "utility.h"

struct SDL_Texture;

namespace Bolt {

    class BOLT_EXPORT Texture {
    private:
        SDL_Texture* texture;
    public:
        SDL_Texture* getTexture() const;

        explicit Texture(SDL_Texture* texture) : texture{texture} {};
        ~Texture();

        //Make Non-copyable, likely to pass around as shared_ptr
        Texture() = delete;
        Texture(const Texture &) = delete;
        Texture &operator=(const Texture &) = delete;
        Texture(Texture &&) noexcept = default;
        Texture &operator=(Texture &&) = default;
    };

}

#endif //BOLT_TEXTURE_H
