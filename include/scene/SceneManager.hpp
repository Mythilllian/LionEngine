#pragma once
#include "scene/Scene.hpp"
#include <vector>

namespace GameEngine {
class SceneManager {
public:
    SceneManager();
    void loadScene(Scene* scene);
    Scene* getCurrentScene() const;
    Scene* saveSceneState() const;
    void init();
    void start();
    void update(float deltaTime);
    void shutdown();
    std::vector<SpriteRenderer*> getSpriteRenderersInCurrentScene() const;
private:
    Scene* currentScene = nullptr;
};
}