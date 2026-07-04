#pragma once
#include <chrono>

namespace GameEngine {
class Time {
public:
    void update();
    float deltaTime() const;
    float elapsedTime() const;
private:
    std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
    float deltaTimeValue = 0.0f;
    float elapsedTimeValue = 0.0f;
};
}