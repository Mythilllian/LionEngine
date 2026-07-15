#pragma once
#include <cmath>
#include <nlohmann/json.hpp>

namespace LionEngine {
class Vector2;
class Vector2i {
public:
    int x, y;
    Vector2i(int x = 0, int y = 0);
    Vector2i(const Vector2& other);
    Vector2i operator+(const Vector2i& other) const;
    Vector2i operator-(const Vector2i& other) const;
    Vector2i operator*(const Vector2i& other) const;
    Vector2i operator/(const Vector2i& other) const;
    Vector2i operator*(int scalar) const;
    Vector2i operator/(int scalar) const;
    Vector2i operator+=(const Vector2i& other);
    Vector2i operator-=(const Vector2i& other);
    Vector2i operator*=(const Vector2i& other);
    Vector2i operator/=(const Vector2i& other);
    Vector2i operator*=(int scalar);
    Vector2i operator/=(int scalar);
    bool operator==(const Vector2i& other) const;
    bool operator!=(const Vector2i& other) const;
    float dotProduct(const Vector2i& other) const;
    float magnitude() const;
    static const Vector2i DOWN;
    static const Vector2i LEFT;
    static const Vector2i ONE;
    static const Vector2i RIGHT;
    static const Vector2i UP;
    static const Vector2i ZERO;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector2i, x, y)
}