#pragma once
#include "graphics/Color.hpp"
#include "graphics/Renderer.hpp"
#include "math/Vector2i.hpp"
#include <SDL.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace GameEngine {
class Renderer;
struct Sprite {
public:
    Sprite(Color tintColor = Color::WHITE);
    virtual ~Sprite() = default;
    bool visible = true;
    Color tint = Color::WHITE;
    virtual Vector2i getSize() const = 0;
    virtual void draw(Renderer* renderer, float x, float y, float width) = 0; // height is calculated to maintain aspect ratio
    virtual void serialize(json& j) const;
    virtual void deserialize(const json& j);
};
void from_json(const json& j, Sprite& u);
void to_json(json& j, const Sprite& u);
}