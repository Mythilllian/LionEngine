#include "LionEngine/math/Direction.hpp"
#include "LionEngine/math/Vector2.hpp"
#include "LionEngine/math/Vector2i.hpp"

namespace LionEngine {
Direction::Direction(float x, float y) : x(x), y(y) {}
Direction::Direction(const Vector2& vec) : x(vec.x), y(vec.y) {}
Direction::Direction(const Vector2i& vec) : x(static_cast<float>(vec.x)), y(static_cast<float>(vec.y)) {}
Direction Direction::fromAngle(float angle) {
    return Direction(std::cos(angle), std::sin(angle));
}
float Direction::angle() const {
    return std::atan2(y, x);
}
const Direction Direction::ZERO = Direction(0, 0);
const Direction Direction::DOWN = Direction(0, -1);
const Direction Direction::LEFT = Direction(-1, 0);
const Direction Direction::RIGHT = Direction(1, 0);
const Direction Direction::UP = Direction(0, 1);
const Direction Direction::DOWNRIGHT = Direction(1, -1);
const Direction Direction::DOWNLEFT = Direction(-1, -1);
const Direction Direction::UPRIGHT = Direction(1, 1);
const Direction Direction::UPLEFT = Direction(-1, 1);
}