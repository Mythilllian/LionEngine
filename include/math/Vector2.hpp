#pragma once
#include <cmath>
#include "math/Vector2i.hpp"

namespace GameEngine {
class Vector2 {
public:
    float x, y;
    Vector2(float x = 0, float y = 0);
    Vector2(const Vector2i& other);
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    float dotProduct(const Vector2& other) const;
    float magnitude() const;
    Vector2 normalized() const;
};
}