#include "core/Time.hpp"

namespace GameEngine {
std::chrono::high_resolution_clock::time_point Time::lastTime = std::chrono::high_resolution_clock::now();
float Time::deltaTimeValue = 0.0f;
float Time::elapsedTimeValue = 0.0f;
void Time::update() {
    auto currentFrameTime = std::chrono::high_resolution_clock::now();
    deltaTimeValue = std::chrono::duration<float>(currentFrameTime - lastTime).count();
    elapsedTimeValue += deltaTimeValue;
    lastTime = currentFrameTime;
}
float Time::deltaTime() {
    return deltaTimeValue;
}
float Time::elapsedTime() {
    return elapsedTimeValue;
}
}