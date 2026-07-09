#pragma once
#include "graphics/Sprite.hpp"
#include "graphics/Color.hpp"
#include "graphics/Renderer.hpp"
#include "assets/Texture.hpp"
#include "math/Vector2i.hpp"
#include <SDL.h>
#include "utils/Logger.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace GameEngine {
class ImageSprite : public Sprite {
public:
    ImageSprite(Texture* texture = nullptr, Color tint = Color::WHITE, Vector2i* srcRect = nullptr);
    ~ImageSprite();
    Texture* texture;
    void setSrcRect(Vector2i* rectSize = nullptr);
    Vector2i getSize() const override;
    Vector2i getSrcRectSize() const;
    bool hasSrcRect() const;
    void draw(Renderer* renderer, float x, float y, float width); // height is calculated to maintain aspect ratio
    void serialize(json& j) const override;
    void deserialize(const json& j) override;
private:
    SDL_Rect* srcRect = nullptr;
};
}