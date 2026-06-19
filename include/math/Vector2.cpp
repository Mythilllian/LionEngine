#include "Vector2.hpp"

namespace GameEngine {
Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::Vector2(const Vector2i& other) {
    x = static_cast<float>(other.x);
    y = static_cast<float>(other.y);
}
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
}