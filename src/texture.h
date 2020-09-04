//
// Created by jack on 8/19/20.
//

#ifndef BOLT_TEXTURE_H
#define BOLT_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>

class Texture {
private:
    SDL_Texture* texture;
public:
    SDL_Texture* getTexture() const;

    explicit Texture(SDL_Texture* t) : texture(t){};
    ~Texture();

    //Make Non-copyable, likely to pass around as shared_ptr
    Texture() = delete;
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&&) noexcept = default;
    Texture& operator=(Texture&&) = default;
};


#endif //BOLT_TEXTURE_H
