#include "graphics/ImageSprite.hpp"

namespace GameEngine{
ImageSprite::ImageSprite(Texture* texture, Color tint, Vector2i* srcRect) : texture(texture), Sprite(tint) {
    setSrcRect(srcRect);
}
ImageSprite::~ImageSprite() {
    delete texture;
}
void ImageSprite::setSrcRect(Vector2i* rectSize) {
    if (srcRect) {
        delete srcRect;
        srcRect = nullptr;
    }
    if (rectSize) {
        srcRect = new SDL_Rect{0, 0, rectSize->x, rectSize->y};
    }
}
Vector2i ImageSprite::getSize() const {
    if (!texture) {
        printf("Sprite getSize failed: No texture loaded.\n");
        return Vector2i(0, 0);
    }
    return texture->getSize();
}
Vector2i ImageSprite::getSrcRectSize() const {
    if (!srcRect) {
        return getSize();
    }
    return Vector2i(srcRect->w, srcRect->h);
}
bool ImageSprite::hasSrcRect() const {
    return srcRect != nullptr;
}
void ImageSprite::draw(Renderer* renderer, float x, float y, float width) {
    if (!visible) return;
    SDL_Texture *sdlTexture = texture->getSDLTexture();
    if (!sdlTexture) {
        Logger::logWarning("Sprite draw failed: Texture not uploaded.");
        return;
    }
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = width;
    dstRect.h = static_cast<int>(width * (static_cast<float>(texture->getSize().y) / texture->getSize().x)); // maintain aspect ratio
    SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_BLEND);
    if(tint.a != 255) {
        SDL_SetTextureAlphaMod(sdlTexture, tint.a);
    }
    SDL_SetTextureColorMod(sdlTexture, tint.r, tint.g, tint.b);
    SDL_RenderCopy(renderer->getSDLRenderer(), sdlTexture, srcRect ? &(*srcRect) : NULL, &dstRect);
}
void ImageSprite::serialize(json& j) const {
    j = json{{"texture", *texture}, {"tint", tint}};
    if (hasSrcRect()) {
        j["srcRect"] = getSrcRectSize();
    }
}
void ImageSprite::deserialize(const json& j) {
    Texture* texture = new Texture();
    j.at("texture").get_to(texture);
    auto tint = j.at("tint").get<Color>();
    auto srcRect = j.contains("srcRect") ? new Vector2i(j.at("srcRect").get<Vector2i>()) : nullptr;
    this->~ImageSprite();
    ::new (this) ImageSprite(texture, tint, srcRect);
}
}