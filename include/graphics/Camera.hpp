#pragma once
#include "math/Vector2.hpp"
#include "math/Vector2i.hpp"

namespace GameEngine{
class Renderer;
class Camera{
public:
    Camera(Vector2i size, Vector2 position = Vector2::ZERO);
    Vector2 position;
    void setCenter(Vector2 center);
    Vector2 getCenter() const;
    void setLeft(float left);
    float getLeft() const;
    void setRight(float right);
    float getRight() const;
    void setTop(float top);
    float getTop() const;
    void setBottom(float bottom);
    float getBottom() const;
    friend class Renderer;
protected:
    Vector2i size;
    void setSize(Vector2i size);
};
}