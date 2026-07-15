#include "LionEngine/graphics/RectSprite.hpp"

namespace LionEngine{
RectSprite::RectSprite(int width, int height, Color fillColor, Color outlineColor, int outlineThickness, bool outlineInRect) : Sprite(), size{width, height}, fillColor(fillColor), outlineColor(outlineColor), outlineThickness(outlineThickness), outlineInRect(outlineInRect) {}
RectSprite::RectSprite(Vector2i size, Color fillColor, Color outlineColor, int outlineThickness, bool outlineInRect) : Sprite(), size(size), fillColor(fillColor), outlineColor(outlineColor), outlineThickness(outlineThickness), outlineInRect(outlineInRect) {}
Vector2i RectSprite::getSize() const {
    return size;
}
void RectSprite::draw(Renderer* renderer, float x, float y, float width, float height) {
    renderer->drawRectSprite(this, x, y, width, height);
}
void RectSprite::serialize(json& j) const {
    j = json{{"size", size}, {"fillColor", fillColor}, {"outlineColor", outlineColor}, {"outlineThickness", outlineThickness}, {"outlineInRect", outlineInRect}};
}
void RectSprite::deserialize(const json& j) {
    if (j.contains("size")) {
        size = j.at("size").get<Vector2i>();
    }
    if (j.contains("fillColor")) {
        fillColor = j.at("fillColor").get<Color>();
    }
    if (j.contains("outlineColor")) {
        outlineColor = j.at("outlineColor").get<Color>();
    }
    if (j.contains("outlineThickness")) {
        outlineThickness = j.at("outlineThickness").get<int>();
    }
    if (j.contains("outlineInRect")) {
        outlineInRect = j.at("outlineInRect").get<bool>();
    }
}
}