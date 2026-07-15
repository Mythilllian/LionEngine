#pragma once
#include "LionEngine/graphics/Color.hpp"
#include "LionEngine/graphics/Renderer.hpp"
#include "LionEngine/math/Vector2i.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace LionEngine {
class Renderer;
struct Sprite {
public:
    Sprite(Color tintColor = Color::WHITE);
    virtual ~Sprite() = default;
    bool visible = true;
    Color tint = Color::WHITE;
    virtual Vector2i getSize() const = 0;
    virtual void draw(Renderer* renderer, float x, float y, float width, float height) = 0;
    float calculateHeightFromWidth(float width) const; // Calculates height needed to maintain aspect ratio
    virtual void serialize(json& j) const;
    virtual void deserialize(const json& j);
};
void from_json(const json& j, Sprite& u);
void to_json(json& j, const Sprite& u);
}