#include "graphics/Renderer.hpp"

namespace GameEngine {
Renderer::Renderer(SDL_Window* window, Color clearColor, int logicalWidth, int logicalHeight) : clearColor(clearColor) {
    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer) {
        printf("Failed to create SDL Renderer: %s\n", SDL_GetError());
    }
    setRenderScaleQuality("0");
    if(logicalWidth <= 0 || logicalHeight <= 0) {
        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        logicalWidth = windowWidth;
        logicalHeight = windowHeight;
    }
    else {
        setLogicalSize(logicalWidth, logicalHeight);
    }
}
Renderer::~Renderer() {
    SDL_DestroyRenderer(sdlRenderer);
}
SDL_Renderer* Renderer::getSDLRenderer() const {
    return sdlRenderer;
}
void Renderer::render(std::vector<SpriteRenderer*>& spriteRenderers) {
    std::sort(spriteRenderers.begin(), spriteRenderers.end(), [](const SpriteRenderer* a, const SpriteRenderer* b) {
        return a->layer < b->layer;
    });
    
    SDL_SetRenderDrawColor(sdlRenderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    SDL_RenderClear(sdlRenderer);
    for (SpriteRenderer* element : spriteRenderers) {
        element->draw(this);
    }
    SDL_RenderPresent(sdlRenderer);
}
void Renderer::setLogicalSize(int width, int height) {
    if(width <= 0 || height <= 0) {
        printf("Invalid logical size: width and height must be greater than 0.\n");
        return;
    }
    SDL_RenderSetLogicalSize(sdlRenderer, width, height);
    logicalSize = Vector2i(width, height);
}
Vector2i Renderer::getLogicalSize() const {
    return logicalSize;
}
void Renderer::setRenderScaleQuality(const std::string& quality) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, quality.c_str());
}
}