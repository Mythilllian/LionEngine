#include "LionEngine/ecs/Rigidbody.hpp"
#include "LionEngine/ecs/Entity.hpp"
#include "LionEngine/core/Engine.hpp"
#include "LionEngine/ecs/Collider.hpp"

namespace LionEngine {
Rigidbody::Rigidbody(Entity* parent) : Component(parent) {
    SERIALIZEFIELD(mass);
    SERIALIZEFIELD(drag);
    SERIALIZEFIELD(bounciness);
    SERIALIZEFIELD(velocity);
    SERIALIZEFIELD(gravityScale);
    SERIALIZEFIELD(isKinematic);
}
void Rigidbody::start() {
    int thisIndex = parent->getComponentIndex<Rigidbody>();
    int colliderIndex = parent->getComponentIndex<Collider>();
    if(colliderIndex != -1 && thisIndex > colliderIndex) {
        parent->swapComponentIndices<Rigidbody, Collider>();
    }
}
void Rigidbody::update(float deltaTime) {
    if(isKinematic) {
        return;
    }
    Physics physics = Engine::instance().physics();
    velocity -= velocity * drag * deltaTime;
    velocity += Vector2(physics.gravityDirection) * physics.gravity * gravityScale * deltaTime;
    Transform globalTransform = parent->globalTransform();
    globalTransform.position += velocity * deltaTime;
    parent->updateGlobalTransform(globalTransform);
}
void Rigidbody::addForce(const Vector2& force) {
    velocity += force / mass;
}
void Rigidbody::addForce(float x, float y) {
    addForce(Vector2(x, y));
}
}
