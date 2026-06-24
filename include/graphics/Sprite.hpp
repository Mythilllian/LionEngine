#pragma once
#include "graphics/Color.hpp"
#include "graphics/Renderer.hpp"
#include <SDL.h>

namespace GameEngine {
class Renderer;
struct Sprite {
public:
    Sprite(Color tintColor = Color::WHITE);
    virtual ~Sprite() = default;
    bool visible = true;
    Color tint = Color::WHITE;
    virtual void draw(Renderer* renderer, float x, float y, float width) = 0; // height is calculated to maintain aspect ratio
};
}