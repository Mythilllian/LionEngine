#pragma once
#include "scene/Entity.hpp"

namespace GameEngine {
class Entity;
class Component {
public:
    Component(Entity* parent) : parent(parent) {}
    virtual ~Component() = default;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void shutdown() = 0;
    virtual Component* clone(Entity* newParent) = 0;
    bool active = true;
protected:
    Entity* parent;
};
}