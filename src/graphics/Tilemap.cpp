#include "LionEngine/graphics/Tilemap.hpp"

namespace LionEngine {
Tilemap::Tilemap(Texture* texture, Vector2i tileSize, Vector2i spacing, Color tint)
    : texture(texture), tileSize(tileSize), spacing(spacing), tint(tint)
{
    mapSize = texture->getSize() / (tileSize + spacing);
    if(mapSize.x * (tileSize.x + spacing.x) - spacing.x <= texture->getSize().x) {
        mapSize.x += 1;
    }
    if(mapSize.y * (tileSize.y + spacing.y) - spacing.y <= texture->getSize().y) {
        mapSize.y += 1;
    }
}
Vector2i Tilemap::getMapSize() const { return mapSize; }
ImageSprite Tilemap::getTileSprite(int x, int y, Color tint) const {
    if(x < 0 || x >= mapSize.x || y < 0 || y >= mapSize.y) {
        printf("Tile coordinates out of bounds: (%d, %d)\n", x, y);
        return ImageSprite(nullptr);
    }
    int tileX = x * (tileSize.x + spacing.x);
    int tileY = y * (tileSize.y + spacing.y);
    return ImageSprite(texture, this->tint * tint, Rect(tileX, tileY, tileSize.x, tileSize.y));
}
}