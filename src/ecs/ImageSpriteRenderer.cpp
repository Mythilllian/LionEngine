#include "LionEngine/ecs/ImageSpriteRenderer.hpp"
#include "LionEngine/ecs/Entity.hpp"

namespace LionEngine {
ImageSpriteRenderer::ImageSpriteRenderer(Entity* parent) : SpriteRenderer(parent), sprite(nullptr) {
    SERIALIZEFIELD(sprite);
}
void ImageSpriteRenderer::draw(Renderer* renderer) {
    if (sprite == nullptr) {
        return;
    }
    Transform transform = parent->globalTransform();
    if(parent->centerTransform) {
        transform.position.x -= transform.scale.x * 0.5f;
        transform.position.y -= transform.scale.x * 0.5f;
    }
    float width = resizeToEntity ? transform.scale.x : sprite->getSize().x;
    float height = keepAspectRatio ? sprite->calculateHeightFromWidth(width) : sprite->getSize().y;
    sprite->draw(renderer, transform.position.x, transform.position.y, width, height);
}
}