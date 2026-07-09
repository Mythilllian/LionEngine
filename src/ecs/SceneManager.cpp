#include "ecs/SceneManager.hpp"
#include "ecs/ImageSpriteRenderer.hpp"

namespace GameEngine {
SceneManager::SceneManager(AssetManager* assetManager) : assetManager(assetManager), currentScene(nullptr) {}
SceneManager::SceneManager(AssetManager* assetManager, Scene* scene) : assetManager(assetManager) { loadScene(scene); }
SceneManager::SceneManager(AssetManager* assetManager, const std::string& path) : assetManager(assetManager) { loadScene(path); }
void SceneManager::loadScene(Scene* scene) {
    if (currentScene) {
        currentScene->shutdown();
        delete currentScene;
    }
    currentScene = scene;
    assetManager->uploadUnloadedTextures();
    currentScene->init();
    currentScene->start();
}
void SceneManager::loadScene(const std::string& path) {
    if (currentScene) {
        currentScene->shutdown();
        delete currentScene;
    }
    &assetManager->loadJson(path).get_to(currentScene);
    assetManager->uploadUnloadedTextures();
    currentScene->init();
    currentScene->start();
}
Scene* SceneManager::getCurrentScene() const {
    return currentScene;
}
Scene* SceneManager::saveSceneState() const {
    if (currentScene) {
        return currentScene->clone();
    }
    return nullptr;
}
void SceneManager::init() {
    if (currentScene) {
        currentScene->init();
    }
}
void SceneManager::start() {
    if (currentScene) {
        currentScene->start();
    }
}
void SceneManager::update(float deltaTime) {
    if (currentScene) {
        currentScene->update(deltaTime);
    }
}
void SceneManager::shutdown() {
    if (currentScene) {
        currentScene->shutdown();
        delete currentScene;
        currentScene = nullptr;
    }
}
std::vector<SpriteRenderer*> SceneManager::getSpriteRenderersInCurrentScene() const {
    if (currentScene) {
        return currentScene->getSpriteRenderers();
    }
    return {};
}
}