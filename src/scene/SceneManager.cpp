#include "scene/SceneManager.hpp"

namespace GameEngine {
SceneManager::SceneManager() : currentScene(nullptr) {}
void SceneManager::loadScene(Scene* scene) {
    if (currentScene) {
        currentScene->shutdown();
        delete currentScene;
    }
    currentScene = scene;
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