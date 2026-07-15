#pragma once
#include "LionEngine/ecs/SpriteRenderer.hpp"
#include "LionEngine/graphics/RectSprite.hpp"

namespace LionEngine {
class Renderer;
class Sprite;
class RectSpriteRenderer : public SpriteRenderer {
public:
    RectSpriteRenderer(Entity* parent);
    RectSprite* sprite;
    void draw(Renderer* renderer) override;
};
REGISTERCOMPONENT(RectSpriteRenderer)
}