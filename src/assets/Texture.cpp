#include "assets/Texture.hpp"
#include <SDL_image.h>

namespace GameEngine {
Texture::Texture(const std::string& path, SDL_Renderer* renderer) : Asset(path) {
    texture = IMG_LoadTexture(renderer, path.c_str());
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
Vector2i Texture::getSize() const {
    return size;
}
}