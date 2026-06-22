#pragma once

#include <SDL.h>
#include "graphics/Sprite.hpp"
#include "graphics/Color.hpp"
#include "math/Vector2i.hpp"

namespace GameEngine{
class RectSprite : public Sprite {
public:
    RectSprite(int width, int height, Color fillColor = Color::WHITE, Color outlineColor = Color::BLACK, int outlineThickness = 1, bool outlineInRect = false);
    RectSprite(Vector2i size, Color fillColor = Color::WHITE, Color outlineColor = Color::BLACK, int outlineThickness = 1, bool outlineInRect = false);
    Vector2i size;
    Color fillColor = Color::WHITE;
    Color outlineColor = Color::BLACK;
    int outlineThickness = 0;
    bool outlineInRect = false;
    void draw(SDL_Renderer* renderer, int x, int y, int width) override;
};
}