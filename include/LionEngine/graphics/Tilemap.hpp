#pragma once
#include "LionEngine/assets/Texture.hpp"
#include "LionEngine/math/Vector2i.hpp"
#include "LionEngine/graphics/Color.hpp"
#include "LionEngine/graphics/ImageSprite.hpp"
#include "LionEngine/math/Rect.hpp"
#include <nlohmann/json.hpp>

namespace LionEngine {
class Tilemap {
public:
    Tilemap(Texture* texture, Vector2i tileSize, Vector2i spacing = Vector2i::ZERO, Color tint = Color::WHITE);
    Vector2i getMapSize() const;
    ImageSprite getTileSprite(int x, int y, Color tint = Color::WHITE) const;
    Color tint;
private:
    Texture* texture;
    Vector2i tileSize;
    Vector2i spacing;
    Vector2i mapSize; // measured in tiles
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Tilemap, texture, tileSize, spacing, mapSize, tint)
}