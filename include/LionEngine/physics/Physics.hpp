#pragma once
#include "LionEngine/math/Direction.hpp"

namespace LionEngine {
struct Physics {
    Physics(float gravity = 9.81f, Direction gravityDirection = {0, -1}) : gravity(gravity), gravityDirection(gravityDirection) {}
    float gravity = 9.81f; // m/s^2
    Direction gravityDirection = {0, -1};
};
}