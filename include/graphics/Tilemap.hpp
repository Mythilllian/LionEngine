#pragma once
#include "assets/Texture.hpp"
#include "math/Vector2i.hpp"
#include "graphics/Color.hpp"
#include "graphics/ImageSprite.hpp"
#include <nlohmann/json.hpp>

namespace GameEngine {
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