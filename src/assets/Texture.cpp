#include "assets/Texture.hpp"

namespace GameEngine {
std::vector<Texture*> Texture::unloadedTextures;
Texture::Texture(const std::string& path) : Asset(path) {
    load();
}
Texture::Texture() : Asset() {}
void Texture::load(const std::string& path) {
    if(path != "") {
        this->path = path;
    }
    if(texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if(surface) {
        SDL_FreeSurface(surface);
        surface = nullptr;
    }
    surface = IMG_Load(this->path.c_str());
    if (!surface) {
        Logger::logWarning("Failed to load texture surface: %s", SDL_GetError());
    }
    unloadedTextures.push_back(this);
}
void Texture::upload(Renderer& renderer)
{
    if(texture) {
        Logger::logWarning("Texture already uploaded: %s", path.c_str());
        return;
    }
    if(!surface) {
        Logger::logWarning("Texture upload failed: Surface not loaded.");
        return;
    }
    texture = SDL_CreateTextureFromSurface(
        renderer.getSDLRenderer(),
        surface);
    if (!texture) {
        Logger::logWarning("Failed to load texture: %s", SDL_GetError());
    }
    else {
        unloadedTextures.erase(std::remove(unloadedTextures.begin(), unloadedTextures.end(), this), unloadedTextures.end());
        size = Vector2i(surface->w, surface->h);
    }
}
Texture::~Texture() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
SDL_Texture* Texture::getSDLTexture() const {
    return texture;
}
SDL_Surface* Texture::getSDLSurface() const {
    return surface;
}
Vector2i Texture::getSize() const {
    if(!texture) {
        Logger::logWarning("Texture getSize failed: Texture not uploaded.");
        return Vector2i(0, 0);
    }
    return size;
}
bool Texture::loaded() const {
    return path != "" && surface != nullptr && texture != nullptr;
}
void from_json(const json& j, Texture& u)
{
    auto path = j.at("path").get<std::string>();
    u.load(path);
}
void to_json(json& j, const Texture& u)
{
    j = json{{"path", u.path}};
}
}