#pragma once
#include <string>
#include "LionEngine/graphics/Color.hpp"
#include "LionEngine/math/Vector2.hpp"
#include "LionEngine/math/Vector2i.hpp"
#include "LionEngine/math/Direction.hpp"
#include <nlohmann/json.hpp>

namespace LionEngine {
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
    bool roundToLogicalUnit = false;
    
    // Engine options
    int targetFPS = 60;
    std::string assetDirectory = "Assets";
    std::string startupScenePath = "";

    // Logging options
    std::string logDirectory = "Logs";
    std::string logFile = "log";
    bool outputToFile = false;
    bool outputToConsole = true;
    bool outputInfoToConsole = true;
    bool outputWarningToConsole = true;
    bool outputErrorToConsole = true;
    bool timestampEnabled = true;

    // Physics options
    float gravity = 9.81f; // m/s^2
    Direction gravityDirection = Direction(0, -1);
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Config, 
    windowSize, windowTitle, fullscreen, resizeable, bordered, 
    clearColor, logicalSize, roundToLogicalUnit,
    targetFPS, assetDirectory, startupScenePath,
    logDirectory, logFile, outputToFile, outputToConsole, outputInfoToConsole, outputWarningToConsole, outputErrorToConsole, timestampEnabled,
    gravity, gravityDirection
)
}