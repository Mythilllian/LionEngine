#pragma once

#include "LionEngine/graphics/Sprite.hpp"
#include "LionEngine/graphics/Color.hpp"
#include "LionEngine/math/Vector2i.hpp"
#include "LionEngine/graphics/Renderer.hpp"

namespace LionEngine{
struct RectSprite : public Sprite {
    RectSprite(int width, int height, Color fillColor = Color::WHITE, Color outlineColor = Color::BLACK, int outlineThickness = 0, bool outlineInRect = false);
    RectSprite(Vector2i size = Vector2i(0, 0), Color fillColor = Color::WHITE, Color outlineColor = Color::BLACK, int outlineThickness = 0, bool outlineInRect = false);
    Vector2i size;
    Color fillColor = Color::WHITE;
    Color outlineColor = Color::BLACK;
    int outlineThickness = 0;
    bool outlineInRect = false;
    Vector2i getSize() const override;
    void draw(Renderer* renderer, float x, float y, float width, float height) override;
    void serialize(json& j) const override;
    void deserialize(const json& j) override;
};
}