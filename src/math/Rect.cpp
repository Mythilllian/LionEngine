#include "LionEngine/math/Rect.hpp"

namespace LionEngine {
Rect::Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
Rect::Rect(Vector2 position, Vector2 size) : x(position.x), y(position.y), width(size.x), height(size.y) {}
Rect::Rect(float width, float height) : x(0), y(0), width(width), height(height) {}
Rect::Rect(Vector2 size) : x(0), y(0), width(size.x), height(size.y) {}
Rect::Rect() : x(0), y(0), width(0), height(0) {}
float Rect::area() const {
    return width * height;
}
float Rect::perimeter() const {
    return 2 * (width + height);
}
bool Rect::isZero() const {
    return width == 0 && height == 0;
}
Vector2 Rect::getPosition() const {
    return Vector2(x, y);
}
Vector2 Rect::getSize() const {
    return Vector2(width, height);
}
bool Rect::operator==(const Rect& other) const {
    return x == other.x && y == other.y && width == other.width && height == other.height;
}
bool Rect::operator!=(const Rect& other) const {
    return !(*this == other);
}
}