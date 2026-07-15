#include "LionEngine/ecs/RectSpriteRenderer.hpp"
#include "LionEngine/ecs/Entity.hpp"

namespace LionEngine {
RectSpriteRenderer::RectSpriteRenderer(Entity* parent) : SpriteRenderer(parent), sprite(nullptr) {
    SERIALIZEFIELD(sprite);
}
void RectSpriteRenderer::draw(Renderer* renderer) {
    if (sprite == nullptr) {
        return;
    }
    Transform transform = parent->globalTransform();
    if(parent->centerTransform) {
        transform.position.x -= transform.scale.x * 0.5f;
        transform.position.y -= transform.scale.x * 0.5f;
    }
    float width;
    float height;
    if(resizeToEntity) {
        width = transform.scale.x;
        height = keepAspectRatio ? sprite->calculateHeightFromWidth(width) : transform.scale.y;
    } else {
        width = sprite->getSize().x;
        height = keepAspectRatio ? sprite->calculateHeightFromWidth(width) : sprite->getSize().y;
    }
    sprite->draw(renderer, transform.position.x, transform.position.y, width, height);
}
}