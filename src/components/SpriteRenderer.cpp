#include "components/SpriteRenderer.hpp"

namespace GameEngine {
SpriteRenderer::SpriteRenderer(Entity* parent) : Component(parent), sprite(nullptr), layer(0) {}
void SpriteRenderer::draw(Renderer* renderer) {
    if (sprite == nullptr) {
        return;
    }
    Transform transform = parent->globalTransform();
    sprite->draw(renderer, transform.position.x, transform.position.y, transform.scale.x);
}
void SpriteRenderer::init() { }
void SpriteRenderer::start() { }
void SpriteRenderer::update(float deltaTime) { }
void SpriteRenderer::shutdown() { }
}