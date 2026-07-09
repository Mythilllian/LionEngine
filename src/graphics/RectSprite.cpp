#include "graphics/RectSprite.hpp"

namespace GameEngine{
RectSprite::RectSprite(int width, int height, Color fillColor, Color outlineColor, int outlineThickness, bool outlineInRect) : Sprite(), size{width, height}, fillColor(fillColor), outlineColor(outlineColor), outlineThickness(outlineThickness), outlineInRect(outlineInRect) {}
RectSprite::RectSprite(Vector2i size, Color fillColor, Color outlineColor, int outlineThickness, bool outlineInRect) : Sprite(), size(size), fillColor(fillColor), outlineColor(outlineColor), outlineThickness(outlineThickness), outlineInRect(outlineInRect) {}
Vector2i RectSprite::getSize() const {
    return size;
}
void RectSprite::draw(Renderer* renderer, float x, float y, float width) {
    if (!visible) return;
    if (size.x <= 0 || size.y <= 0) return;

    int width_ = static_cast<int>(width);
    int height = static_cast<int>(width * (static_cast<float>(size.y) / size.x));
    int _x = static_cast<int>(x);
    int _y = static_cast<int>(y);
    SDL_SetRenderDrawBlendMode(renderer->getSDLRenderer(), SDL_BLENDMODE_BLEND);
    if(outlineThickness > 0) {
        SDL_Rect outlineRect = { _x - (outlineInRect ? 0 : outlineThickness), _y - (outlineInRect ? 0 : outlineThickness), width_ + (outlineInRect ? 0 : outlineThickness * 2), height + (outlineInRect ? 0 : outlineThickness * 2) };
        SDL_SetRenderDrawColor(renderer->getSDLRenderer(), outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
        SDL_RenderFillRect(renderer->getSDLRenderer(), &outlineRect);
    }
    SDL_Rect fillRect = { _x + (outlineInRect ? outlineThickness : 0), _y + (outlineInRect ? outlineThickness : 0), width_ - (outlineInRect ? outlineThickness * 2 : 0), height - (outlineInRect ? outlineThickness * 2 : 0) };
    SDL_SetRenderDrawColor(renderer->getSDLRenderer(), fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer->getSDLRenderer(), &fillRect);
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