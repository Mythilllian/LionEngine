#pragma once
#include "LionEngine/core/Config.hpp"
#include "LionEngine/core/Time.hpp"
#include "LionEngine/core/Game.hpp"
#include "LionEngine/core/PersistentData.hpp"
#include "LionEngine/graphics/Renderer.hpp"
#include "LionEngine/ecs/SceneManager.hpp"
#include "LionEngine/audio/AudioManager.hpp"
#include "LionEngine/assets/AssetManager.hpp"
#include "LionEngine/graphics/Window.hpp"
#include "LionEngine/physics/Physics.hpp"
#include "LionEngine/input/Input.hpp"
#include "LionEngine/utils/Logger.hpp"
#include "LionEngine/serialization/JsonPointerSerializer.hpp"
#include <nlohmann/json.hpp>

namespace LionEngine {
class Input;
class Time;
class Engine {
public:
    Engine(const Config& config = Config(), Game* game = nullptr);
    Engine(const std::string& configPath);
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
    Physics& physics();
    const Physics& physics() const;
    Window& window();
    const Window& window() const;
    Renderer& renderer();
    const Renderer& renderer() const;
    PersistentData& persistentData();
    const PersistentData& persistentData() const;
    Config& config();
    const Config& config() const;
private:
    bool running;
    static Engine* instance_;
    Config config_;
    PersistentData persistentData_;
    Window window_;
    Renderer renderer_;
    SceneManager sceneManager_;
    AudioManager audioManager_;
    AssetManager assetManager_;
    Physics physics_;
    Game* game_;
};
}