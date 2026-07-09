#pragma once
#include "ecs/SpriteRenderer.hpp"
#include "graphics/ImageSprite.hpp"

namespace GameEngine {
class Renderer;
class Sprite;
class ImageSpriteRenderer : public SpriteRenderer {
public:
    ImageSpriteRenderer(Entity* parent);
    ImageSprite* sprite;
    ~ImageSpriteRenderer() override = default;
    void draw(Renderer* renderer) override;
};
REGISTERCOMPONENT(ImageSpriteRenderer)
}