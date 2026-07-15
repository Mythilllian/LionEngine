#pragma once
#include "LionEngine/ecs/Scene.hpp"
#include <vector>
#include "LionEngine/assets/AssetManager.hpp"
#include "LionEngine/utils/FileSystem.hpp"

namespace LionEngine {
class SceneManager {
public:
    SceneManager(AssetManager* assetManager);
    SceneManager(AssetManager* assetManager, Scene* scene);
    SceneManager(AssetManager* assetManager, const std::string& path);
    void loadScene(Scene* scene);
    void loadScene(const std::string& path);
    Scene* getCurrentScene() const;
    Scene* saveSceneState() const;
    void init();
    void start();
    void update(float deltaTime);
    void shutdown();
    std::vector<SpriteRenderer*> getSpriteRenderersInCurrentScene() const;
private:
    Scene* currentScene = nullptr;
    AssetManager* assetManager = nullptr;
};
}