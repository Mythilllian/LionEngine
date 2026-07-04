#pragma once
#include <string>
#include "graphics/Color.hpp"
#include "math/Vector2i.hpp"

namespace GameEngine {
struct Config {
    // Window options
    Vector2i windowSize = Vector2i(800, 600);
    std::string windowTitle = "Game";
    bool fullscreen = false;
    bool resizeable = true;

    // Renderer options
    Color clearColor = Color(0, 0, 0, 255);
    Vector2i logicalSize = Vector2i(-1, -1);
    
    // Engine options
    int targetFPS = 60;
    std::string assetDirectory = "assets";

    // Logging options
    std::string logDirectory = "logs";
    std::string logFile = "log.txt";
    bool logToFile = true;
    bool logToConsole = true;
};
}