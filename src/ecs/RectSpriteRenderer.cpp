#include "ecs/RectSpriteRenderer.hpp"
#include "ecs/Entity.hpp"

namespace GameEngine {
RectSpriteRenderer::RectSpriteRenderer(Entity* parent) : SpriteRenderer(parent), sprite(nullptr) {
    SERIALIZEFIELD(layer);
    SERIALIZEFIELD(sprite);
}
void RectSpriteRenderer::draw(Renderer* renderer) {
    if (sprite == nullptr) {
        return;
    }
    Transform transform = parent->globalTransform();
    sprite->draw(renderer, transform.position.x, transform.position.y, transform.scale.x);
}
}