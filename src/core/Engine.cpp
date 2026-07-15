#include "LionEngine/core/Engine.hpp"

namespace LionEngine {
Engine::Engine(const Config& config, Game* game)
    : config_(config),
      window_(config_.windowSize, config_.windowTitle, config_.fullscreen, config_.resizeable, config_.bordered),
      renderer_(window_, config_.clearColor, config_.logicalSize, config_.roundToLogicalUnit),
      audioManager_(),
      assetManager_(config_.assetDirectory, &renderer_),
      sceneManager_(&assetManager_),
      game_(game),
      physics_(config_.gravity, config_.gravityDirection)
{
    instance_ = this;

    Logger::logDirectory = config_.logDirectory;
    Logger::logFile = config_.logFile;
    Logger::outputToFile = config_.outputToFile;
    Logger::outputToConsole = config_.outputToConsole;
    Logger::outputInfoToConsole = config_.outputInfoToConsole;
    Logger::outputWarningToConsole = config_.outputWarningToConsole;
    Logger::outputErrorToConsole = config_.outputErrorToConsole;
    Logger::timestampEnabled = config_.timestampEnabled;

    if(config.startupScenePath != "") {
        sceneManager_.loadScene(config.startupScenePath);
    }
}
Engine::Engine(const std::string& configPath)
    : Engine(json::parse(FileSystem::readFile(configPath)), nullptr) {}
Engine::~Engine() {
    instance_ = nullptr;
    Logger::logInfo("Game engine shut down.");
    Logger::closeLog();
}
void Engine::run() {
    Logger::logInfo("Game engine running.");
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
        Time::update();

        float deltaTime = Time::deltaTime();
        sceneManager_.update(deltaTime);
        auto renderers = sceneManager_.getSpriteRenderersInCurrentScene();
        renderer_.render(renderers);

        SDL_Delay(1000 / config_.targetFPS);

        if (Input::wasQuitRequested()) {
            Logger::logInfo("Quit requested through input.");
            running = false;
        }
    }

    sceneManager_.shutdown();
    if (game_) {
        game_->shutdown();
    }
}
void Engine::shutdown() {
    Logger::logInfo("Shutting down game engine.");
    running = false;
}
Engine& Engine::instance() {
    return *instance_;
}
SceneManager& Engine::sceneManager() { return sceneManager_; }
const SceneManager& Engine::sceneManager() const { return sceneManager_; }
AudioManager& Engine::audioManager() { return audioManager_; }
const AudioManager& Engine::audioManager() const { return audioManager_; }
AssetManager& Engine::assetManager() { return assetManager_; }
const AssetManager& Engine::assetManager() const { return assetManager_; }
Physics& Engine::physics() { return physics_; }
const Physics& Engine::physics() const { return physics_; }
Window& Engine::window() { return window_; }
const Window& Engine::window() const { return window_; }
Renderer& Engine::renderer() { return renderer_; }
const Renderer& Engine::renderer() const { return renderer_; }
PersistentData& Engine::persistentData() { return persistentData_; }
const PersistentData& Engine::persistentData() const { return persistentData_; }
Config& Engine::config() { return config_; }
const Config& Engine::config() const { return config_; }
Engine* Engine::instance_ = nullptr;
}