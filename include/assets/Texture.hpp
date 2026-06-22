#pragma once

#include "assets/Asset.hpp"
#include "math/Vector2i.hpp"
#include <SDL.h>

namespace GameEngine {
class Texture : public Asset {
public:
    Texture(const std::string& path, SDL_Renderer* renderer);
    ~Texture() override;
    SDL_Texture* getSDLTexture() const;
    Vector2i getSize() const;
private:
    SDL_Texture* texture;
    Vector2i size{0,0};
};
}