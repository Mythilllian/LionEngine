#include "LionEngine/graphics/Camera.hpp"

namespace LionEngine
{
Camera::Camera(Vector2i size, Vector2 position) : size(size), position(position) {}
void Camera::setCenter(Vector2 center)
{
    position = center - Vector2(size.x / 2.0f, size.y / 2.0f);
}
Vector2 Camera::getCenter() const
{
    return position + Vector2(size.x / 2.0f, size.y / 2.0f);
}
void Camera::setLeft(float left)
{
    position.x = left;
}
float Camera::getLeft() const
{
    return position.x;
}
void Camera::setRight(float right)
{
    position.x = right - size.x;
}
float Camera::getRight() const
{
    return position.x + size.x;
}
void Camera::setTop(float top)
{
    position.y = top;
}
float Camera::getTop() const
{
    return position.y;
}
void Camera::setBottom(float bottom)
{
    position.y = bottom - size.y;
}
float Camera::getBottom() const
{
    return position.y + size.y;
}
void Camera::setSize(Vector2i size)
{
    this->size = size;
}
}