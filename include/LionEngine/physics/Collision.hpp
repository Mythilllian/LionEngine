#pragma once
#include "LionEngine/math/Vector2.hpp"

namespace LionEngine {
class Collider;
struct Collision {
public:
    Collider* thisCollider;
    Collider* otherCollider;
    Vector2 normal;
    float penetrationDepth;
    bool isTrigger = false;
    bool operator==(const Collision& other) const {
        return (thisCollider == other.thisCollider && otherCollider == other.otherCollider) ||
               (thisCollider == other.otherCollider && otherCollider == other.thisCollider);
    }
    Collision fromCollider(Collider* collider) const {
        if (thisCollider == collider) {
            return {thisCollider, otherCollider, normal, penetrationDepth};
        } else if (otherCollider == collider) {
            return {otherCollider, thisCollider, normal, penetrationDepth};
        } else {
            Logger::logError("Collider not part of this collision");
        }
    }
};
struct RaycastHit {
public:
    Collider* collider;
    Vector2 point;
    Vector2 normal;
    float distance;
};
}