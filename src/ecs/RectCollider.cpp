#include "LionEngine/ecs/RectCollider.hpp"
#include "LionEngine/ecs/Entity.hpp"

namespace LionEngine {
RectCollider::RectCollider(Entity* parent) : Collider(parent) {
    SERIALIZEFIELD(size);
}
void RectCollider::update(float deltaTime) {
    if(resizeToEntity) {
        size = parent->globalTransform().scale;
    }
    touchingTop_ = false;
    touchingBottom_ = false;
    touchingLeft_ = false;
    touchingRight_ = false;
    Collider::update(deltaTime);
}
bool RectCollider::touchingTop() const {
    return touchingTop_;
}
bool RectCollider::touchingBottom() const {
    return touchingBottom_;
}
bool RectCollider::touchingLeft() const {
    return touchingLeft_;
}
bool RectCollider::touchingRight() const {
    return touchingRight_;
}
std::vector<Collision> RectCollider::checkCollision() {
    std::vector<Collider*> colliders = getActiveColliders();
    std::vector<Collision> collisions;
    for(Collider* other : colliders) {
        RectCollider* otherRect = dynamic_cast<RectCollider*>(other);
        if(otherRect) {
            Transform thisTransform = parent->globalTransform(false);
            Transform otherTransform = otherRect->parent->globalTransform(false);
            Vector2 thisMin = thisTransform.position + offset;
            Vector2 thisMax = thisTransform.position + size + offset;
            Vector2 otherMin = otherTransform.position + otherRect->offset;
            Vector2 otherMax = otherTransform.position + otherRect->size + otherRect->offset;
            if(thisMax.x > otherMin.x && thisMin.x < otherMax.x && thisMax.y > otherMin.y && thisMin.y < otherMax.y) {
                // Collision happened
                // Calculate penetration depth and collision normal
                float xOverlap = std::min(thisMax.x, otherMax.x) - std::max(thisMin.x, otherMin.x);
                float yOverlap = std::min(thisMax.y, otherMax.y) - std::max(thisMin.y, otherMin.y);
                Vector2 normal;
                float penetrationDepth;
                bool isPhysicalCollision = isTrigger ? true : !otherRect->isTrigger;
                if(xOverlap < yOverlap) {
                    if(thisTransform.position.x < otherTransform.position.x) {
                        normal = Vector2(-1, 0);
                        if(isPhysicalCollision) {
                            touchingRight_ = true;
                        }
                    } else {
                        normal = Vector2(1, 0);
                        if(isPhysicalCollision) {
                            touchingLeft_ = true;
                        }
                    }
                    penetrationDepth = xOverlap;
                } else {
                    if(thisTransform.position.y > otherTransform.position.y) {
                        normal = Vector2(0, 1);
                        if(isPhysicalCollision) {
                            touchingBottom_ = true;
                        }
                    } else {
                        normal = Vector2(0, -1);
                        if(isPhysicalCollision) {
                            touchingTop_ = true;
                        }
                    }
                    penetrationDepth = yOverlap;
                }
                collisions.push_back({this, otherRect, normal, penetrationDepth, isTrigger || otherRect->isTrigger});
            }
        }
    }
    return collisions;
}
}