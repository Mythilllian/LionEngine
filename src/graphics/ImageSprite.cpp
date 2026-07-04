#include "graphics/ImageSprite.hpp"

namespace GameEngine{
ImageSprite::ImageSprite(Texture* texture, Color tint) : texture(texture), Sprite(tint) {}
ImageSprite::~ImageSprite() {
    delete texture;
}
Vector2i ImageSprite::getSize() const {
    if (!texture) {
        printf("Sprite getSize failed: No texture loaded.\n");
        return Vector2i(0, 0);
    }
    return texture->getSize();
}
void ImageSprite::draw(Renderer* renderer, float x, float y, float width) {
    if (!visible) return;
    if (!texture) {
        printf("Sprite draw failed: No texture loaded.\n");
        return;
    }
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = width;
    dstRect.h = static_cast<int>(width * (static_cast<float>(texture->getSize().y) / texture->getSize().x)); // maintain aspect ratio
    SDL_SetTextureBlendMode(texture->getSDLTexture(), SDL_BLENDMODE_BLEND);
    if(tint.a != 255) {
        SDL_SetTextureAlphaMod(texture->getSDLTexture(), tint.a);
    }
    SDL_SetTextureColorMod(texture->getSDLTexture(), tint.r, tint.g, tint.b);
    SDL_RenderCopy(renderer->getSDLRenderer(), texture->getSDLTexture(), srcRect ? &(*srcRect) : NULL, &dstRect);
}
}