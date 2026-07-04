#pragma once
#include "SDL.h"
#include <string>
#include "assets/Texture.hpp"
#include "math/Vector2i.hpp"

namespace GameEngine {
class Window {
public:
    Window(Vector2i size, std::string name = "Game", Uint32 flags = SDL_WINDOW_SHOWN);
    ~Window();
    SDL_Window* getSDLWindow() const;
    void maximize();
    void minimize();
    void setFullscreen(bool fullscreen);
    void setBorderered(bool bordered);
    void setResizable(bool resizable);
    Vector2i getSize() const;
    Vector2i getPosition() const;
    void setSize(int width, int height);
    void setSize(Vector2i size);
    void setPosition(int x, int y);
    void setTitle(const std::string& title);
    void showWindow();
    void hideWindow();
    void setIcon(Texture& texture);
private:
    SDL_Window* window;
};
}