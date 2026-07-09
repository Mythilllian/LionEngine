#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include "graphics/Color.hpp"
#include "ecs/SpriteRenderer.hpp"
#include "math/Vector2i.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Window.hpp"
#include "utils/Logger.hpp"

namespace GameEngine{
class Camera;
class SpriteRenderer;
class Renderer{
public:
    Renderer(Window& window, Color clearColor = Color(0, 0, 0, 255), Vector2i logicalSize = Vector2i(256, 224));
    ~Renderer();
    SDL_Renderer* getSDLRenderer() const;
    void render(std::vector<SpriteRenderer*>& spriteRenderers);
    Color clearColor;
    Camera* getCamera() const;
    void setLogicalSize(int width, int height);
    Vector2i getLogicalSize() const;
    void setRenderScaleQuality(const std::string& quality);
private:
    SDL_Renderer* sdlRenderer;
    Vector2i logicalSize;
    Camera* camera;
};
}