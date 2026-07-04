#pragma once
#include "scene/Entity.hpp"
#include "components/SpriteRenderer.hpp"
#include <vector>

namespace GameEngine {
class Scene {
public:
    Scene();
    ~Scene() = default;
    void init();
    void start();
    void update(float deltaTime);
    void shutdown();
    void addEntity(Entity* entity);
    Entity* getRootEntity();
    std::vector<SpriteRenderer*> getSpriteRenderers() const;
    Scene* clone() const;
private:
    Entity root;
};
}