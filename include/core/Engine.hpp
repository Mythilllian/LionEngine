#pragma once
#include "core/Config.hpp"
#include "core/Time.hpp"
#include "core/Game.hpp"
#include "graphics/Renderer.hpp"
#include "ecs/SceneManager.hpp"
#include "audio/AudioManager.hpp"
#include "assets/AssetManager.hpp"
#include "graphics/Window.hpp"
#include "input/Input.hpp"
#include "utils/Logger.hpp"
#include "serialization/JsonPointerSerializer.hpp"

namespace GameEngine {
class Input;
class Time;
class Engine {
public:
    Engine(const Config& config, Game* game = nullptr);
    ~Engine();
    void run();
    void shutdown();
    static Engine& instance();
    SceneManager& sceneManager();
    const SceneManager& sceneManager() const;
    AudioManager& audioManager();
    const AudioManager& audioManager() const;
    AssetManager& assetManager();
    const AssetManager& assetManager() const;
private:
    bool running;
    static Engine* instance_;
    Config config_;
    Window window_;
    Renderer renderer_;
    SceneManager sceneManager_;
    AudioManager audioManager_;
    AssetManager assetManager_;
    Game* game_;
};
}