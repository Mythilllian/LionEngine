#include "math/Vector2i.hpp"

namespace GameEngine {
Vector2i::Vector2i(int x, int y) : x(x), y(y) {}
Vector2i Vector2i::operator+(const Vector2i& other) const {
    return Vector2i(x + other.x, y + other.y);
}
Vector2i Vector2i::operator-(const Vector2i& other) const {
    return Vector2i(x - other.x, y - other.y);
}
Vector2i Vector2i::operator*(int scalar) const {
    return Vector2i(x * scalar, y * scalar);
}
Vector2i Vector2i::operator/(int scalar) const {
    return Vector2i(x / scalar, y / scalar);
}
float Vector2i::dotProduct(const Vector2i& other) const {
    return x * other.x + y * other.y;
}
float Vector2i::magnitude() const {
    return std::sqrt(x * x + y * y);
}
}