#pragma once
#include <string>
#include "graphics/Color.hpp"
#include "math/Vector2i.hpp"
#include <nlohmann/json.hpp>

namespace GameEngine {
struct Config {
    // Window options
    Vector2i windowSize = Vector2i(800, 600);
    std::string windowTitle = "Game";
    bool fullscreen = false;
    bool resizeable = true;
    bool bordered = true;

    // Renderer options
    Color clearColor = Color(0, 0, 0, 255);
    Vector2i logicalSize = Vector2i(-1, -1);
    
    // Engine options
    int targetFPS = 60;
    std::string assetDirectory = "assets";
    std::string startupScenePath = "scenes/scene1.json";

    // Logging options
    std::string logDirectory = "logs";
    std::string logFile = "log.txt";
    bool outputToFile = false;
    bool outputToConsole = true;
    bool outputInfoToConsole = true;
    bool outputWarningToConsole = true;
    bool outputErrorToConsole = true;
    bool timestampEnabled = true;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, 
    windowSize, windowTitle, fullscreen, resizeable, bordered, 
    clearColor, logicalSize, 
    targetFPS, assetDirectory, startupScenePath,
    logDirectory, logFile, outputToFile, outputToConsole, outputInfoToConsole, outputWarningToConsole, outputErrorToConsole, timestampEnabled
)
}