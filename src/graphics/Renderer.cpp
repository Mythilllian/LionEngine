#include "LionEngine/graphics/Renderer.hpp"
#include "LionEngine/graphics/ImageSprite.hpp"
#include "LionEngine/graphics/RectSprite.hpp"

namespace LionEngine {
Renderer::Renderer(Window& window, Color clearColor, Vector2i logicalSize, bool roundToLogicalUnit) : window(window), clearColor(clearColor), roundToLogicalUnit(roundToLogicalUnit) {
    sdlRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer) {
        Logger::logError("Failed to create SDL Renderer: %s", SDL_GetError());
    }
    setRenderScaleQuality("0");
    if(logicalSize.x <= 0 || logicalSize.y <= 0) {
        logicalSize = Vector2i(window.getSize());
        camera = new Camera(logicalSize);
    }
    else {
        camera = new Camera(logicalSize);
        setLogicalSize(logicalSize.x, logicalSize.y);
    }
}
Renderer::~Renderer() {
    SDL_DestroyRenderer(sdlRenderer);
}
SDL_Renderer* Renderer::getSDLRenderer() const {
    return sdlRenderer;
}
void Renderer::render(std::vector<SpriteRenderer*>& spriteRenderers) {
    std::sort(spriteRenderers.begin(), spriteRenderers.end(), [](const SpriteRenderer* a, const SpriteRenderer* b) {
        return a->layer < b->layer;
    });
    SDL_SetRenderDrawColor(sdlRenderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    SDL_RenderClear(sdlRenderer);
    SDL_Rect cameraRect = { -static_cast<int>(camera->position.x), -static_cast<int>(camera->position.y), camera->size.x, camera->size.y };
    SDL_RenderSetViewport(sdlRenderer, &cameraRect);
    for (SpriteRenderer* element : spriteRenderers) {
        element->draw(this);
    }
    SDL_RenderPresent(sdlRenderer);
}
void Renderer::setCamera(Camera* newCamera) {
    if (camera) {
        delete camera;
    }
    camera = newCamera;
}
Camera* Renderer::getCamera() const {
    return camera;
}
void Renderer::setLogicalSize(int width, int height) {
    if(width <= 0 || height <= 0) {
        Logger::logWarning("Invalid logical size: width and height must be greater than 0.");
        return;
    }
    SDL_RenderSetLogicalSize(sdlRenderer, width, height);
    logicalSize = Vector2i(width, height);
    camera->setSize(logicalSize);
    resetLogicalUnit();
}
Vector2i Renderer::getLogicalSize() const {
    return logicalSize;
}
void Renderer::setRenderScaleQuality(const std::string& quality) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, quality.c_str());
}
void Renderer::drawImageSprite(ImageSprite* sprite, float x, float y, float width, float height) {
    if (!sprite->visible) return;
    SDL_Texture *sdlTexture = sprite->texture->getSDLTexture();
    if (!sdlTexture) {
        Logger::logWarning("Sprite draw failed: Texture not uploaded.");
        return;
    }
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = logicalSize.y - static_cast<int>(y) - static_cast<int>(height); // flip y-axis
    dstRect.w = width;
    dstRect.h = static_cast<int>(width * (static_cast<float>(sprite->texture->getSize().y) / sprite->texture->getSize().x)); // maintain aspect ratio
    if(roundToLogicalUnit) {
        dstRect.x = Round::toNearest(dstRect.x, logicalUnit);
        dstRect.y = Round::toNearest(dstRect.y, logicalUnit);
        dstRect.w = Round::toNearest(dstRect.w, logicalUnit);
        dstRect.h = Round::toNearest(dstRect.h, logicalUnit);
    }
    SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_BLEND);
    if(sprite->tint.a != 255) {
        SDL_SetTextureAlphaMod(sdlTexture, sprite->tint.a);
    }
    SDL_SetTextureColorMod(sdlTexture, sprite->tint.r, sprite->tint.g, sprite->tint.b);
    if(sprite->hasSrcRect()) {
        SDL_Rect srcRect = { static_cast<int>(sprite->srcRect.x), static_cast<int>(sprite->srcRect.y), static_cast<int>(sprite->srcRect.width), static_cast<int>(sprite->srcRect.height) };
        SDL_RenderCopy(sdlRenderer, sdlTexture, &srcRect, &dstRect);
    } else {
        SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &dstRect);
    }
}
void Renderer::drawRectSprite(RectSprite* sprite, float x, float y, float width, float height) {
    if (!sprite->visible) return;
    int _width = static_cast<int>(width);
    int _height = static_cast<int>(height);
    if (_width <= 0 || _height <= 0) return;
    int _x = static_cast<int>(x);
    int _y = logicalSize.y - static_cast<int>(y) - _height; // flip y-axis
    if(roundToLogicalUnit) {
        _x = Round::toNearest(_x, logicalUnit);
        _y = Round::toNearest(_y, logicalUnit);
        _width = Round::toNearest(_width, logicalUnit);
        _height = Round::toNearest(_height, logicalUnit);
    }
    SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
    if(sprite->outlineThickness > 0) {
        SDL_Rect outlineRect = { _x - (sprite->outlineInRect ? 0 : sprite->outlineThickness), _y - (sprite->outlineInRect ? 0 : sprite->outlineThickness), _width + (sprite->outlineInRect ? 0 : sprite->outlineThickness * 2), _height + (sprite->outlineInRect ? 0 : sprite->outlineThickness * 2) };
        SDL_SetRenderDrawColor(sdlRenderer, sprite->outlineColor.r, sprite->outlineColor.g, sprite->outlineColor.b, sprite->outlineColor.a);
        SDL_RenderFillRect(sdlRenderer, &outlineRect);
    }
    SDL_Rect fillRect = { _x + (sprite->outlineInRect ? sprite->outlineThickness : 0), _y + (sprite->outlineInRect ? sprite->outlineThickness : 0), _width - (sprite->outlineInRect ? sprite->outlineThickness * 2 : 0), _height - (sprite->outlineInRect ? sprite->outlineThickness * 2 : 0) };
    SDL_SetRenderDrawColor(sdlRenderer, sprite->fillColor.r, sprite->fillColor.g, sprite->fillColor.b, sprite->fillColor.a);
    SDL_RenderFillRect(sdlRenderer, &fillRect);
}
void Renderer::resetLogicalUnit() {
    Vector2i logicalSize = getLogicalSize();
    Vector2i windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / logicalSize.x;
    float scaleY = static_cast<float>(windowSize.y) / logicalSize.y;
    logicalUnit = static_cast<int>(std::floor(std::min(scaleX, scaleY)));
}
}