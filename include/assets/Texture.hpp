#pragma once

#include "assets/Asset.hpp"
#include "math/Vector2i.hpp"
#include <SDL.h>
#include <SDL_image.h>

namespace GameEngine {
class Renderer;
class Texture : public Asset {
public:
    Texture(const std::string& path, Renderer* renderer);
    ~Texture() override;
    SDL_Texture* getSDLTexture() const;
    SDL_Surface* getSDLSurface() const;
    Vector2i getSize() const;
private:
    SDL_Texture* texture;
    Vector2i size{0,0};
};
}