#pragma once

#include <string>

namespace GameEngine{
class Renderer{
public:
    void loadTexture(const std::string& filename);
    void drawSprite(int x, int y);
    void drawRect(int x, int y, int width, int height);
    void drawText(const std::string& text, int x, int y);
    void present();
};
}