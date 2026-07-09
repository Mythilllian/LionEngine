#pragma once
#include "ecs/Entity.hpp"
#include "ecs/SpriteRenderer.hpp"
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Scene, root)
private:
    Entity root;
};
}