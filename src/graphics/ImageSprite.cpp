#include "LionEngine/graphics/ImageSprite.hpp"
#include "LionEngine/graphics/Renderer.hpp"

namespace LionEngine{
ImageSprite::ImageSprite(Texture* texture, Color tint, Rect srcRect) : texture(texture), Sprite(tint), srcRect(srcRect) {}
ImageSprite::~ImageSprite() {
    delete texture;
}
Vector2i ImageSprite::getSize() const {
    if (!texture) {
        printf("Sprite getSize failed: No texture loaded.\n");
        return Vector2i(0, 0);
    }
    if(hasSrcRect()) {
        return srcRect.getSize();
    }
    return texture->getSize();
}
bool ImageSprite::hasSrcRect() const {
    return !srcRect.isZero();
}
void ImageSprite::draw(Renderer* renderer, float x, float y, float width, float height) {
    renderer->drawImageSprite(this, x, y, width, height);
}
void ImageSprite::serialize(json& j) const {
    j = json{{"texture", *texture}, {"tint", tint}};
    if (hasSrcRect()) {
        j["srcRect"] = srcRect;
    }
}
void ImageSprite::deserialize(const json& j) {
    Texture* texture = new Texture();
    j.at("texture").get_to(texture);
    auto tint = j.at("tint").get<Color>();
    auto srcRect = j.contains("srcRect") ? j.at("srcRect").get<Rect>() : Rect();
    this->~ImageSprite();
    ::new (this) ImageSprite(texture, tint, srcRect);
}
}