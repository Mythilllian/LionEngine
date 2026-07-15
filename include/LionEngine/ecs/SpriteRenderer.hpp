#pragma once
#include "LionEngine/ecs/Component.hpp"
#include "LionEngine/ecs/Transform.hpp"
#include "LionEngine/graphics/Renderer.hpp"
#include "LionEngine/graphics/Sprite.hpp"
#include "LionEngine/ecs/Entity.hpp"

namespace LionEngine {
class Renderer;
class Sprite;
class SpriteRenderer : public Component {
public:
    SpriteRenderer(Entity* parent);
    Sprite* sprite;
    int layer;
    bool resizeToEntity = true;
    bool keepAspectRatio = true;
    virtual void draw(Renderer* renderer) = 0;
};
}