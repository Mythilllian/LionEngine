#pragma once
#include "graphics/Sprite.hpp"
#include "graphics/Color.hpp"
#include "assets/Texture.hpp"
#include <optional>

namespace GameEngine {
class ImageSprite : public Sprite {
public:
    ImageSprite(Texture* texture, Color tint = Color::WHITE);
    ~ImageSprite();
    Texture* texture;
    std::optional<SDL_Rect> srcRect = std::nullopt;
    void draw(SDL_Renderer* renderer, int x, int y, int width); // height is calculated to maintain aspect ratio
};
}