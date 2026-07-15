#pragma once
#include <chrono>

namespace LionEngine {
class Engine;
class Time {
public:
    static float deltaTime();
    static float elapsedTime();
    friend class Engine;
private:
    static void update();
    static std::chrono::high_resolution_clock::time_point lastTime;
    static float deltaTimeValue;
    static float elapsedTimeValue;
};
}