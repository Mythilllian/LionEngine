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

    float height = width * (static_cast<float>(size.y) / size.x);
    int _x = static_cast<int>(x);
    int _y = static_cast<int>(y);
    SDL_SetRenderDrawBlendMode(renderer->getSDLRenderer(), SDL_BLENDMODE_BLEND);
    if(outlineThickness > 0) {
        SDL_Rect outlineRect = { _x - (outlineInRect ? 0 : outlineThickness), _y - (outlineInRect ? 0 : outlineThickness), width + (outlineInRect ? 0 : outlineThickness * 2), height + (outlineInRect ? 0 : outlineThickness * 2) };
        SDL_SetRenderDrawColor(renderer->getSDLRenderer(), outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
        SDL_RenderFillRect(renderer->getSDLRenderer(), &outlineRect);
    }
    SDL_Rect fillRect = { _x + (outlineInRect ? outlineThickness : 0), _y + (outlineInRect ? outlineThickness : 0), width - (outlineInRect ? outlineThickness * 2 : 0), height - (outlineInRect ? outlineThickness * 2 : 0) };
    SDL_SetRenderDrawColor(renderer->getSDLRenderer(), fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer->getSDLRenderer(), &fillRect);
}
}