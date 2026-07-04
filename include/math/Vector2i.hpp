#pragma once
#include <cmath>
#include "math/Vector2.hpp"

namespace GameEngine {
class Vector2i {
public:
    int x, y;
    Vector2i(int x = 0, int y = 0);
    Vector2i(const Vector2& other);
    Vector2i operator+(const Vector2i& other) const;
    Vector2i operator-(const Vector2i& other) const;
    Vector2i operator*(int scalar) const;
    Vector2i operator/(int scalar) const;
    Vector2i operator+=(const Vector2i& other);
    Vector2i operator-=(const Vector2i& other);
    Vector2i operator*=(int scalar);
    Vector2i operator/=(int scalar);
    bool operator==(const Vector2i& other) const;
    bool operator!=(const Vector2i& other) const;
    float dotProduct(const Vector2i& other) const;
    float magnitude() const;
    Vector2 toVector2() const;
    static const Vector2i DOWN;
    static const Vector2i LEFT;
    static const Vector2i ONE;
    static const Vector2i RIGHT;
    static const Vector2i UP;
    static const Vector2i ZERO;
};
}