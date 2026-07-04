#pragma once
#include "components/Component.hpp"
#include "components/Transform.hpp"
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
    SpriteRenderer* clone(Entity* newParent) override;
    void draw(Renderer* renderer);
};
}