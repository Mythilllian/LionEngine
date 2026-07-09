#include "math/Vector2i.hpp"

namespace GameEngine {
Vector2i::Vector2i(int x, int y) : x(x), y(y) {}
Vector2i::Vector2i(const Vector2& other) {
    x = static_cast<int>(other.x);
    y = static_cast<int>(other.y);
}
Vector2i Vector2i::operator+(const Vector2i& other) const {
    return Vector2i(x + other.x, y + other.y);
}
Vector2i Vector2i::operator-(const Vector2i& other) const {
    return Vector2i(x - other.x, y - other.y);
}
Vector2i Vector2i::operator*(const Vector2i& other) const {
    return Vector2i(x * other.x, y * other.y);
}
Vector2i Vector2i::operator/(const Vector2i& other) const {
    return Vector2i(x / other.x, y / other.y);
}
Vector2i Vector2i::operator*(int scalar) const {
    return Vector2i(x * scalar, y * scalar);
}
Vector2i Vector2i::operator/(int scalar) const {
    return Vector2i(x / scalar, y / scalar);
}
Vector2i Vector2i::operator+=(const Vector2i& other) {
    x += other.x;
    y += other.y;
    return *this;
}
Vector2i Vector2i::operator-=(const Vector2i& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}
Vector2i Vector2i::operator*=(const Vector2i& other) {
    x *= other.x;
    y *= other.y;
    return *this;
}
Vector2i Vector2i::operator/=(const Vector2i& other) {
    x /= other.x;
    y /= other.y;
    return *this;
}
Vector2i Vector2i::operator*=(int scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}
Vector2i Vector2i::operator/=(int scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}
bool Vector2i::operator==(const Vector2i& other) const {
    return x == other.x && y == other.y;
}
bool Vector2i::operator!=(const Vector2i& other) const {
    return !(*this == other);
}
float Vector2i::dotProduct(const Vector2i& other) const {
    return x * other.x + y * other.y;
}
float Vector2i::magnitude() const {
    return std::sqrt(x * x + y * y);
}
Vector2 Vector2i::toVector2() const {
    return Vector2(static_cast<float>(x), static_cast<float>(y));
}
const Vector2i Vector2i::DOWN{0, -1};
const Vector2i Vector2i::LEFT{-1, 0};
const Vector2i Vector2i::ONE{1, 1};
const Vector2i Vector2i::RIGHT{1, 0};
const Vector2i Vector2i::UP{0, 1};
const Vector2i Vector2i::ZERO{0, 0};
}