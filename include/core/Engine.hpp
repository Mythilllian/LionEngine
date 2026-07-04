#pragma once
#include "core/Config.hpp"
#include "core/Time.hpp"
#include "core/Game.hpp"
#include "graphics/Renderer.hpp"
#include "scene/SceneManager.hpp"
#include "audio/AudioManager.hpp"
#include "assets/AssetManager.hpp"
#include "graphics/Window.hpp"
#include "input/Input.hpp"

namespace GameEngine {
class Input;
class Engine {
public:
    Engine(const Config& config, Game* game = nullptr);
    ~Engine() = default;
    void run();
    void shutdown();
    SceneManager& sceneManager();
    const SceneManager& sceneManager() const;
    AudioManager& audioManager();
    const AudioManager& audioManager() const;
    AssetManager& assetManager();
    const AssetManager& assetManager() const;
    float getElapsedTime() const;
private:
    bool running;
    Config config_;
    Window window_;
    Renderer renderer_;
    SceneManager sceneManager_;
    AudioManager audioManager_;
    AssetManager assetManager_;
    Time time_;
    Game* game_;
};
}