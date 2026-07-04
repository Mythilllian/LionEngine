#pragma once
#include "graphics/Sprite.hpp"
#include "graphics/Color.hpp"
#include "graphics/Renderer.hpp"
#include "assets/Texture.hpp"
#include "math/Rect.hpp"
#include "math/Vector2i.hpp"

namespace GameEngine {
struct ImageSprite : public Sprite {
    ImageSprite(Texture* texture, Color tint = Color::WHITE);
    ~ImageSprite();
    Texture* texture;
    SDL_Rect* srcRect = nullptr;;
    Vector2i getSize() const override;
    void draw(Renderer* renderer, float x, float y, float width); // height is calculated to maintain aspect ratio
};
}