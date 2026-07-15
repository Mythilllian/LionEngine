#pragma once
#include "LionEngine/ecs/Component.hpp"
#include "LionEngine/physics/Collision.hpp"
#include <vector>
#include <algorithm>
#include <iterator>

namespace LionEngine {
class Collider : public Component {
public:
    Collider(Entity* parent);
    void start() override;
    void update(float deltaTime) override;
    bool isTrigger = false;
    bool resizeToEntity = true;
    Vector2 offset = Vector2(0, 0);
    float percentCorrectedPerStep = 0.8f; // fraction of penetration corrected per step
    float slop = 0.01f; // small allowed overlap to avoid jitter
protected:
    std::vector<Collider*> getActiveColliders() const; 
private:
    virtual std::vector<Collision> checkCollision() = 0;
    std::vector<Collision> currentCollisions;
};
}