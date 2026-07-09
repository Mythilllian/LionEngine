#include "ecs/SpriteRenderer.hpp"

namespace GameEngine {
SpriteRenderer::SpriteRenderer(Entity* parent) : Component(parent), sprite(nullptr), layer(0) {}
void SpriteRenderer::draw(Renderer* renderer) { }
void SpriteRenderer::init() { }
void SpriteRenderer::start() { }
void SpriteRenderer::update(float deltaTime) { }
void SpriteRenderer::shutdown() { }
}