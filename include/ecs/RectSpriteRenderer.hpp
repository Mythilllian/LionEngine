#pragma once
#include "ecs/SpriteRenderer.hpp"
#include "graphics/RectSprite.hpp"

namespace GameEngine {
class Renderer;
class Sprite;
class RectSpriteRenderer : public SpriteRenderer {
public:
    RectSpriteRenderer(Entity* parent);
    RectSprite* sprite;
    ~RectSpriteRenderer() override = default;
    void draw(Renderer* renderer) override;
};
REGISTERCOMPONENT(RectSpriteRenderer)
}