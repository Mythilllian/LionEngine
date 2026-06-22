#include "graphics/RectSprite.hpp"

namespace GameEngine{
RectSprite::RectSprite(int width, int height, Color fillColor, Color outlineColor, int outlineThickness, bool outlineInRect) : Sprite(), size{width, height}, fillColor(fillColor), outlineColor(outlineColor), outlineThickness(outlineThickness), outlineInRect(outlineInRect) {}
RectSprite::RectSprite(Vector2i size, Color fillColor, Color outlineColor, int outlineThickness, bool outlineInRect) : Sprite(), size(size), fillColor(fillColor), outlineColor(outlineColor), outlineThickness(outlineThickness), outlineInRect(outlineInRect) {}
void RectSprite::draw(SDL_Renderer* renderer, int x, int y, int width) {
    if (!visible) return;
    if (size.x <= 0 || size.y <= 0) return;

    int height = static_cast<int>(width * (static_cast<float>(size.y) / size.x));

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    if(outlineThickness > 0) {
        SDL_Rect outlineRect = { x - (outlineInRect ? 0 : outlineThickness), y - (outlineInRect ? 0 : outlineThickness), width + (outlineInRect ? 0 : outlineThickness * 2), height + (outlineInRect ? 0 : outlineThickness * 2) };
        SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
        SDL_RenderFillRect(renderer, &outlineRect);
    }
    SDL_Rect fillRect = { x + (outlineInRect ? outlineThickness : 0), y + (outlineInRect ? outlineThickness : 0), width - (outlineInRect ? outlineThickness * 2 : 0), height - (outlineInRect ? outlineThickness * 2 : 0) };
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer, &fillRect);
}
}