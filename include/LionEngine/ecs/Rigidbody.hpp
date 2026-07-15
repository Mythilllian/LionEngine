#pragma once
#include "LionEngine/ecs/Component.hpp"
#include "LionEngine/math/Vector2.hpp"

namespace LionEngine {
class Rigidbody : public Component {
public:
    Rigidbody(Entity* parent);
    void start() override;
    void update(float deltaTime) override;
    void addForce(const Vector2& force);
    void addForce(float x, float y);
    float mass = 1.0f;
    float drag = 0.1f;
    float bounciness = 0.5f; // restitution coefficient for collision response
    Vector2 velocity = {0, 0};
    float gravityScale = 1.0f;
    bool isKinematic = false;
};
REGISTERCOMPONENT(Rigidbody)
}