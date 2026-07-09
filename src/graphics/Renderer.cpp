#include "graphics/Renderer.hpp"

namespace GameEngine {
Renderer::Renderer(Window& window, Color clearColor, Vector2i logicalSize) : clearColor(clearColor) {
    sdlRenderer = SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer) {
        Logger::logError("Failed to create SDL Renderer: %s", SDL_GetError());
    }
    setRenderScaleQuality("0");
    if(logicalSize.x <= 0 || logicalSize.y <= 0) {
        logicalSize = Vector2i(window.getSize());
        camera = new Camera(logicalSize);
    }
    else {
        camera = new Camera(logicalSize);
        setLogicalSize(logicalSize.x, logicalSize.y);
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
    SDL_Rect cameraRect = { -static_cast<int>(camera->position.x), -static_cast<int>(camera->position.y), camera->size.x, camera->size.y };
    SDL_RenderSetViewport(sdlRenderer, &cameraRect);
    for (SpriteRenderer* element : spriteRenderers) {
        element->draw(this);
    }
    SDL_RenderPresent(sdlRenderer);
}
Camera* Renderer::getCamera() const {
    return camera;
}
void Renderer::setLogicalSize(int width, int height) {
    if(width <= 0 || height <= 0) {
        Logger::logWarning("Invalid logical size: width and height must be greater than 0.");
        return;
    }
    SDL_RenderSetLogicalSize(sdlRenderer, width, height);
    logicalSize = Vector2i(width, height);
    camera->setSize(logicalSize);
}
Vector2i Renderer::getLogicalSize() const {
    return logicalSize;
}
void Renderer::setRenderScaleQuality(const std::string& quality) {
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, quality.c_str());
}
}