#include "scene/Scene.hpp"

namespace GameEngine {
Scene::Scene() : root(nullptr, "Root") {}
void Scene::init() {
    root.init();
}
void Scene::start() {
    root.start();
}
void Scene::update(float deltaTime) {
    root.update(deltaTime);
}
void Scene::shutdown() {
    root.shutdown();
}
void Scene::addEntity(Entity* entity) {
    root.addChild(entity);
}
Entity* Scene::getRootEntity() {
    return &root;
}
std::vector<SpriteRenderer*> Scene::getSpriteRenderers() const {
    return root.getComponentsInDescendants<SpriteRenderer>();
}
Scene* Scene::clone() const {
    Scene* newScene = new Scene();
    newScene->root = *root.clone();
    return newScene;
}
}