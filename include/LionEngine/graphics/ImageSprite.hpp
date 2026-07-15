#pragma once
#include "LionEngine/graphics/Sprite.hpp"
#include "LionEngine/graphics/Color.hpp"
#include "LionEngine/assets/Texture.hpp"
#include "LionEngine/math/Vector2i.hpp"
#include "LionEngine/utils/Logger.hpp"
#include "LionEngine/math/Rect.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace LionEngine {
class Renderer;
struct ImageSprite : public Sprite {
    ImageSprite(Texture* texture = nullptr, Color tint = Color::WHITE, Rect srcRect = Rect());
    ~ImageSprite();
    Texture* texture;
    Vector2i getSize() const override;
    bool hasSrcRect() const;
    void draw(Renderer* renderer, float x, float y, float width, float height) override;
    void serialize(json& j) const override;
    void deserialize(const json& j) override;
    Rect srcRect = Rect();
};
}