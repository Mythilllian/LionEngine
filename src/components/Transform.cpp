#include "components/Transform.hpp"

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
}