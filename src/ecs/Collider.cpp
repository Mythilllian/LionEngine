#include "LionEngine/ecs/Collider.hpp"
#include "LionEngine/ecs/Entity.hpp"
#include "LionEngine/ecs/Rigidbody.hpp"
#include "LionEngine/core/Engine.hpp"

namespace LionEngine {
Collider::Collider(Entity* parent) : Component(parent) 
{
    SERIALIZEFIELD(isTrigger);
    SERIALIZEFIELD(resizeToEntity);
    SERIALIZEFIELD(offset);
    SERIALIZEFIELD(percentCorrectedPerStep);
    SERIALIZEFIELD(slop);
}
void Collider::start() {
    int thisIndex = parent->getComponentIndex<Collider>();
    int rigidbodyIndex = parent->getComponentIndex<Rigidbody>();
    if(rigidbodyIndex != -1 && thisIndex < rigidbodyIndex) {
        parent->swapComponentIndices<Collider, Rigidbody>();
    }
}
void Collider::update(float deltaTime) {
    std::vector<Collision> collisions = checkCollision();
    std::vector<Collision> currentCollisionsCopy(currentCollisions);
    for (const auto& collision : collisions) {
        if(currentCollisionsCopy.end() != std::find(currentCollisionsCopy.begin(), currentCollisionsCopy.end(), collision)) {
            // Collision stay
            parent->callEvent("onCollisionStay", false, (void*)&collision);
            // collision.otherCollider->parent->callEvent("onCollisionStay", false, &collision.fromCollider(collision.otherCollider));
            currentCollisionsCopy.erase(std::remove(currentCollisionsCopy.begin(), currentCollisionsCopy.end(), collision), currentCollisionsCopy.end());
        } else {
            // Collision enter
            currentCollisions.push_back(collision);
            parent->callEvent("onCollisionEnter", false, (void*)&collision);
            // collision.otherCollider->parent->callEvent("onCollisionEnter", false, &collision.fromCollider(collision.otherCollider));
        }
    }
    for (const auto& collision : currentCollisionsCopy) {
        // Collision exit
        if (std::find(collisions.begin(), collisions.end(), collision) == collisions.end()) {
            currentCollisions.erase(std::remove(currentCollisions.begin(), currentCollisions.end(), collision), currentCollisions.end());
            parent->callEvent("onCollisionExit", false, (void*)&collision);
            // collision.otherCollider->parent->callEvent("onCollisionExit", false, &collision.fromCollider(collision.otherCollider));
        }
    }
    if(isTrigger || collisions.empty()) {
        return;
    }
    
    //Resolve collisions if there are Rigidbody components on both colliders
    Rigidbody *thisRigidbody = parent->getComponent<Rigidbody>();
    if(!thisRigidbody || !thisRigidbody->active) {
        return;
    }
 
    for (const auto& collision : collisions) {
        if(collision.isTrigger) {
            continue;
        }
        Rigidbody* otherRigidbody = collision.otherCollider->parent->getComponent<Rigidbody>();

        float correctionMag = std::max(collision.penetrationDepth - slop, 0.0f) * percentCorrectedPerStep;
 
        if(otherRigidbody && otherRigidbody->active && !otherRigidbody->isKinematic) {
            // Collision response with dynamic object
            float invMassSum = 1 / thisRigidbody->mass + 1 / otherRigidbody->mass;
 
            Vector2 correction = collision.normal * (correctionMag / invMassSum);
            Transform thisT = parent->globalTransform();
            thisT.position += correction / thisRigidbody->mass;
            parent->updateGlobalTransform(thisT);
            // Transform otherT = otherRigidbody->getParent()->globalTransform();
            // otherT.position -= correction / otherRigidbody->mass;
            // otherRigidbody->getParent()->updateGlobalTransform(otherT);
 
            Vector2 relativeVelocity = thisRigidbody->velocity - otherRigidbody->velocity;
            float velocityAlongNormal = relativeVelocity.dotProduct(collision.normal);
            if (velocityAlongNormal > 0) {
                continue;
            }
            float impulseScalar = -(1 + thisRigidbody->bounciness) * velocityAlongNormal;
            impulseScalar /= invMassSum;
            Vector2 impulse = collision.normal * impulseScalar;
            thisRigidbody->velocity += impulse / thisRigidbody->mass;
            // otherRigidbody->velocity -= impulse / otherRigidbody->mass;

        }
        else {
            // Collision response with static collider
            Transform thisT = parent->globalTransform();
            thisT.position += collision.normal * correctionMag;
            parent->updateGlobalTransform(thisT);
 
            float velocityAlongNormal = thisRigidbody->velocity.dotProduct(collision.normal);
            if (velocityAlongNormal > 0) {
                continue;
            }
            float impulseScalar = -(1 + thisRigidbody->bounciness) * velocityAlongNormal;
            impulseScalar *= thisRigidbody->mass;
            Vector2 impulse = collision.normal * impulseScalar;
            thisRigidbody->velocity += impulse / thisRigidbody->mass;
        }
    }
}
std::vector<Collider*> Collider::getActiveColliders() const {
    std::vector<Collider*> colliders = Engine::instance().sceneManager().getCurrentScene()->getRootEntity()->getComponentsInDescendants<Collider>();
    std::vector<Collider*> filtered;
    filtered.reserve(colliders.size());
    std::copy_if(colliders.begin(), colliders.end(), std::back_inserter(filtered), [](Collider* collider) {
        return collider->active && collider->getParent()->active;
    });
    filtered.erase(std::remove(filtered.begin(), filtered.end(), this), filtered.end());
    return filtered;
}
}