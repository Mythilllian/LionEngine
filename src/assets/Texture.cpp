#include "assets/Texture.hpp"
#include "graphics/Renderer.hpp"

namespace GameEngine {
Texture::Texture(const std::string& path, Renderer* renderer) : Asset(path) {
    texture = IMG_LoadTexture(renderer->getSDLRenderer(), path.c_str());
    if (!texture) {
        printf("Failed to load texture: %s\n", SDL_GetError());
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
}
Texture::~Texture() {
    SDL_DestroyTexture(texture);
}
SDL_Texture* Texture::getSDLTexture() const {
    return texture;
}
SDL_Surface* Texture::getSDLSurface() const {
    SDL_Surface *surface = NULL;
    void *pixels = NULL;
    SDL_LockTextureToSurface(texture, NULL, &surface);
    SDL_UnlockTexture(texture);
    return surface;
}
Vector2i Texture::getSize() const {
    return size;
}
}