#include "graphics/Renderer.hpp"
#include <algorithm>

namespace GameEngine{
Renderer::Renderer(SDL_Window* window, int reservedSpriteCount) {
    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer) {
        printf("Failed to create SDL Renderer: %s\n", SDL_GetError());
    }
    sprites.reserve(reservedSpriteCount);
}
Renderer::~Renderer() {
    SDL_DestroyRenderer(sdlRenderer);
}
SDL_Renderer* Renderer::getSDLRenderer() const {
    return sdlRenderer;
}
void Renderer::registerSprite(Sprite* sprite) {
    sprites.push_back(sprite);
}
void Renderer::unregisterSprite(Sprite* sprite) {
    std::erase_if(sprites, [sprite](const Sprite* element) { return element == sprite; });
}
void Renderer::present() {
    for (Sprite* element : sprites) {
        element->draw(sdlRenderer, 0, 0, 100);
    }
    
    SDL_RenderPresent(sdlRenderer);
}
}