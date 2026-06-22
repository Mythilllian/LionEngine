#pragma once
#include <cmath>

namespace GameEngine {
class Vector2 {
public:
    float x, y;
    Vector2(float x = 0, float y = 0);
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    float dotProduct(const Vector2& other) const;
    float magnitude() const;
    Vector2 normalized() const;
    static const Vector2 DOWN;
    static const Vector2 LEFT;
    static const Vector2 ONE;
    static const Vector2 RIGHT;
    static const Vector2 UP;
    static const Vector2 ZERO;
};
}