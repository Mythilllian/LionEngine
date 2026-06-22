#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include "graphics/Sprite.hpp"

namespace GameEngine{
class Renderer{
public:
    Renderer(SDL_Window* window, int reservedSpriteCount = 100);
    ~Renderer();
    SDL_Renderer* getSDLRenderer() const;
    void registerSprite(Sprite* sprite);
    void unregisterSprite(Sprite* sprite);
    void present();
private:
    std::vector<Sprite*> sprites;
    SDL_Renderer* sdlRenderer;
};
}