#pragma once
#include <nlohmann/json.hpp>
#include "LionEngine/math/Vector2.hpp"

namespace LionEngine {
class Rect {
public:
    float x, y, width, height;
    Rect(float x, float y, float width, float height);
    Rect(Vector2 position, Vector2 size);
    Rect(float width, float height);
    Rect(Vector2 size);
    Rect();
    float area() const;
    float perimeter() const;
    bool isZero() const;
    Vector2 getPosition() const;
    Vector2 getSize() const;
    bool operator==(const Rect& other) const;
    bool operator!=(const Rect& other) const;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Rect, x, y, width, height)
}