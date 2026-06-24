#pragma once

#include "graphics/Sprite.hpp"
#include "graphics/Color.hpp"
#include "math/Vector2i.hpp"
#include "graphics/Renderer.hpp"
#include "math/Rect.hpp"
#include <SDL.h>

namespace GameEngine{
struct RectSprite : public Sprite {
    RectSprite(int width, int height, Color fillColor = Color::WHITE, Color outlineColor = Color::BLACK, int outlineThickness = 1, bool outlineInRect = false);
    RectSprite(Vector2i size, Color fillColor = Color::WHITE, Color outlineColor = Color::BLACK, int outlineThickness = 1, bool outlineInRect = false);
    Vector2i size;
    Color fillColor = Color::WHITE;
    Color outlineColor = Color::BLACK;
    int outlineThickness = 0;
    bool outlineInRect = false;
    void draw(Renderer* renderer, float x, float y, float width) override;
};
}