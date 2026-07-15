#pragma once
#include "LionEngine/ecs/SpriteRenderer.hpp"
#include "LionEngine/graphics/ImageSprite.hpp"

namespace LionEngine {
class Renderer;
class Sprite;
class ImageSpriteRenderer : public SpriteRenderer {
public:
    ImageSpriteRenderer(Entity* parent);
    ImageSprite* sprite;
    void draw(Renderer* renderer) override;
};
REGISTERCOMPONENT(ImageSpriteRenderer)
}