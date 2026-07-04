#include "core/Time.hpp"

namespace GameEngine {
void Time::update() {
    auto currentFrameTime = std::chrono::high_resolution_clock::now();
    deltaTimeValue = std::chrono::duration<float>(currentFrameTime - lastTime).count();
    elapsedTimeValue += deltaTimeValue;
    lastTime = currentFrameTime;
}
float Time::deltaTime() const {
    return deltaTimeValue;
}
float Time::elapsedTime() const {
    return elapsedTimeValue;
}
}