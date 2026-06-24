#pragma once
#include "graphics/Sprite.hpp"
#include "graphics/Color.hpp"
#include "graphics/Renderer.hpp"
#include "assets/Texture.hpp"
#include "math/Rect.hpp"
#include <optional>

namespace GameEngine {
struct ImageSprite : public Sprite {
    ImageSprite(Texture* texture, Color tint = Color::WHITE);
    ~ImageSprite();
    Texture* texture;
    std::optional<SDL_Rect> srcRect = std::nullopt;
    void draw(Renderer* renderer, float x, float y, float width); // height is calculated to maintain aspect ratio
};
}