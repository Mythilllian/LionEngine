#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include "graphics/Color.hpp"
#include "components/SpriteRenderer.hpp"
#include "math/Vector2i.hpp"

namespace GameEngine{
class SpriteRenderer;
class Renderer{
public:
    Renderer(SDL_Window* window, Color clearColor = Color(0, 0, 0, 255), int logicalWidth = -1, int logicalHeight = -1);
    ~Renderer();
    SDL_Renderer* getSDLRenderer() const;
    void render(std::vector<SpriteRenderer*>& spriteRenderers);
    Color clearColor;
    void setLogicalSize(int width, int height);
    Vector2i getLogicalSize() const;
    void setRenderScaleQuality(const std::string& quality);
private:
    SDL_Renderer* sdlRenderer;
    Vector2i logicalSize;
};
}