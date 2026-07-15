#pragma once
#include <cmath>
#include <nlohmann/json.hpp>

namespace LionEngine {
class Vector2;
class Vector2i;
struct Direction {
    Direction(float x = 0, float y = 0);
    Direction(const Vector2& vec);
    Direction(const Vector2i& vec);
    float x = 0;
    float y = 0;
    static Direction fromAngle(float angle);
    float angle() const;
    static const Direction ZERO;
    static const Direction DOWN;
    static const Direction LEFT;
    static const Direction RIGHT;
    static const Direction UP;
    static const Direction DOWNRIGHT;
    static const Direction DOWNLEFT;
    static const Direction UPRIGHT;
    static const Direction UPLEFT;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Direction, x, y)
}