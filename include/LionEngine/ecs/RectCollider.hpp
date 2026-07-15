#pragma once
#include "LionEngine/ecs/Collider.hpp"

namespace LionEngine {
class RectCollider : public Collider {
public:
    RectCollider(Entity* parent);
    void update(float deltaTime) override;
    Vector2 size = {0, 0};
    bool touchingTop() const;
    bool touchingBottom() const;
    bool touchingLeft() const;
    bool touchingRight() const;
private:
    std::vector<Collision> checkCollision() override;
    bool touchingTop_ = false;
    bool touchingBottom_ = false;
    bool touchingLeft_ = false;
    bool touchingRight_ = false;
};
REGISTERCOMPONENT(RectCollider)
}