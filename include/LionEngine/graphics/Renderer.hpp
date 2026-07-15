#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include "LionEngine/graphics/Color.hpp"
#include "LionEngine/ecs/SpriteRenderer.hpp"
#include "LionEngine/math/Vector2i.hpp"
#include "LionEngine/graphics/Camera.hpp"
#include "LionEngine/graphics/Window.hpp"
#include "LionEngine/utils/Logger.hpp"
#include "LionEngine/math/Round.hpp"

namespace LionEngine{
class Camera;
class SpriteRenderer;
class ImageSprite;
class RectSprite;
class Renderer{
public:
    Renderer(Window& window, Color clearColor = Color(0, 0, 0, 255), Vector2i logicalSize = Vector2i(256, 224), bool roundToLogicalUnit = false);
    ~Renderer();
    SDL_Renderer* getSDLRenderer() const;
    void render(std::vector<SpriteRenderer*>& spriteRenderers);
    Color clearColor;
    bool roundToLogicalUnit;
    void setCamera(Camera* newCamera);
    Camera* getCamera() const;
    void setLogicalSize(int width, int height);
    Vector2i getLogicalSize() const;
    void setRenderScaleQuality(const std::string& quality);
    void drawImageSprite(ImageSprite* sprite, float x, float y, float width, float height);
    void drawRectSprite(RectSprite* sprite, float x, float y, float width, float height);
    friend void Window::setSize(int width, int height);
private:
    SDL_Renderer* sdlRenderer;
    Vector2i logicalSize;
    Camera* camera;
    Window& window;
    int logicalUnit; // logical units per pixel
    void resetLogicalUnit();
};
}