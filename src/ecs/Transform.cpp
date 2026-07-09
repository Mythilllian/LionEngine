#include "ecs/Transform.hpp"

namespace GameEngine {
Transform Transform::operator*(const Transform& other)
{
    Vector2 newPosition = position + other.position;
    Vector2 newScale = Vector2(scale.x * other.scale.x, scale.y * other.scale.y);
    float newRotation = rotation + other.rotation;
    return Transform(newPosition, newScale, newRotation);
}
Transform Transform::operator/(const Transform& other)
{
    Vector2 newPosition = position - other.position;
    Vector2 newScale = Vector2(scale.x / other.scale.x, scale.y / other.scale.y);
    float newRotation = rotation - other.rotation;
    return Transform(newPosition, newScale, newRotation);
}
bool Transform::operator==(const Transform& other) const
{
    return position == other.position && scale == other.scale && rotation == other.rotation;
}
bool Transform::operator!=(const Transform& other) const
{
    return !(*this == other);
}
}