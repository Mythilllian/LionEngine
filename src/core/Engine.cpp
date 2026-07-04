#include "core/Engine.hpp"

namespace GameEngine {
Engine::Engine(const Config& config, Game* game)
    : config_(config),
      window_(config_.windowSize, config_.windowTitle),
      renderer_(window_, config_.clearColor, config_.logicalSize),
      sceneManager_(),
      audioManager_(),
      assetManager_(config_.assetDirectory, &renderer_),
      game_(game) {}
void Engine::run() {
    if (game_) {
        game_->init();
    }
    sceneManager_.init();
    if (game_) {
        game_->start();
    }
    sceneManager_.start();
    running = true;
    while (running) {
        Input::update();
        time_.update();

        float deltaTime = time_.deltaTime();
        sceneManager_.update(deltaTime);
        auto renderers = sceneManager_.getSpriteRenderersInCurrentScene();
        renderer_.render(renderers);

        SDL_Delay(1000 / config_.targetFPS);

        if (Input::wasQuitRequested()) {
            running = false;
        }
    }
    
}
void Engine::shutdown() {
    running = false;
}
SceneManager& Engine::sceneManager() { return sceneManager_; }
const SceneManager& Engine::sceneManager() const { return sceneManager_; }
AudioManager& Engine::audioManager() { return audioManager_; }
const AudioManager& Engine::audioManager() const { return audioManager_; }
AssetManager& Engine::assetManager() { return assetManager_; }
const AssetManager& Engine::assetManager() const { return assetManager_; }
float Engine::getElapsedTime() const { return time_.elapsedTime(); }
}