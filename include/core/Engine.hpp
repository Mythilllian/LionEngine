#pragma once

#include <SDL.h>

namespace GameEngine {
class Engine {
public:
    void init();
    void run();
    void shutdown();
private:
    bool running = false;
};
}