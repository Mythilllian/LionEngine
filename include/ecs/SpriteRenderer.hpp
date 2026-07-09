#pragma once
#include "ecs/Component.hpp"
#include "ecs/Transform.hpp"
#include "graphics/Renderer.hpp"
#include "graphics/Sprite.hpp"

namespace GameEngine {
class Renderer;
class Sprite;
class SpriteRenderer : public Component {
public:
    SpriteRenderer(Entity* parent);
    Sprite* sprite;
    int layer;
    ~SpriteRenderer() override = default;
    void init() override;
    void start() override;
    void update(float deltaTime) override;
    void shutdown() override;
    virtual void draw(Renderer* renderer);
};
REGISTERCOMPONENT(SpriteRenderer)
}