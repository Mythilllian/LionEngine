#include "math/Vector2.hpp"

namespace GameEngine {
Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}
Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}
Vector2 Vector2::operator/(float scalar) const {
    return Vector2(x / scalar, y / scalar);
}
Vector2 Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}
Vector2 Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}
Vector2 Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}
Vector2 Vector2::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}
bool Vector2::operator==(const Vector2& other) const {
    return x == other.x && y == other.y;
}
bool Vector2::operator!=(const Vector2& other) const {
    return !(*this == other);
}
float Vector2::dotProduct(const Vector2& other) const {
    return x * other.x + y * other.y;
}
float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}
Vector2 Vector2::normalized() const {
    float len = magnitude();
    if (len == 0) return Vector2(0, 0);
    return Vector2(x / len, y / len);
}
const Vector2 Vector2::DOWN{0, -1};
const Vector2 Vector2::LEFT{-1, 0};
const Vector2 Vector2::ONE{1, 1};
const Vector2 Vector2::RIGHT{1, 0};
const Vector2 Vector2::UP{0, 1};
const Vector2 Vector2::ZERO{0, 0};
}