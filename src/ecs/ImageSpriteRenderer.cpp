#include "ecs/ImageSpriteRenderer.hpp"
#include "ecs/Entity.hpp"

namespace GameEngine {
ImageSpriteRenderer::ImageSpriteRenderer(Entity* parent) : SpriteRenderer(parent), sprite(nullptr) {
    SERIALIZEFIELD(layer);
    SERIALIZEFIELD(sprite);
}
void ImageSpriteRenderer::draw(Renderer* renderer) {
    if (sprite == nullptr) {
        return;
    }
    Transform transform = parent->globalTransform();
    sprite->draw(renderer, transform.position.x, transform.position.y, transform.scale.x);
}
}