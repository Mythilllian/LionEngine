#pragma once

#include "math/Vector2.hpp"
#include <nlohmann/json.hpp>

namespace GameEngine
{
struct Transform
{
    Transform(Vector2 position = Vector2{0, 0}, Vector2 scale = Vector2{1, 1}, float rotation = 0) : position(position), scale(scale), rotation(rotation) {}
    virtual ~Transform() = default;
    Vector2 position;
    Vector2 scale;
    float rotation;
    Transform operator*(const Transform& other);
    Transform operator/(const Transform& other);
    bool operator==(const Transform& other) const;
    bool operator!=(const Transform& other) const;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Transform, position, scale, rotation)
}