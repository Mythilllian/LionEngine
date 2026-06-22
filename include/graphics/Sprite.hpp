#pragma once
#include "graphics/Color.hpp"

namespace GameEngine {
struct Sprite {
public:
    Sprite(Color tintColor = Color::WHITE);
    virtual ~Sprite() = default;
    bool visible = true;
    Color tint = Color::WHITE;
    virtual void draw(SDL_Renderer* renderer, int x, int y, int width) = 0; // height is calculated to maintain aspect ratio
};
}