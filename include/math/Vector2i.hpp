#pragma once
#include <cmath>

namespace GameEngine {
class Vector2i {
public:
    int x, y;
    Vector2i(int x = 0, int y = 0);
    Vector2i operator+(const Vector2i& other) const;
    Vector2i operator-(const Vector2i& other) const;
    Vector2i operator*(int scalar) const;
    Vector2i operator/(int scalar) const;
    float dotProduct(const Vector2i& other) const;
    float magnitude() const;
};
}