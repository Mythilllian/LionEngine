#pragma once

#include "LionEngine/assets/Asset.hpp"
#include "LionEngine/math/Vector2i.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "LionEngine/utils/Logger.hpp"
#include "LionEngine/graphics/Renderer.hpp"
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

namespace LionEngine {
class AssetManager;
class Texture : public Asset {
public:
    Texture(const std::string& path);
    Texture();
    ~Texture() override;
    void load(const std::string& path = "");
    void upload(Renderer& renderer);
    SDL_Texture* getSDLTexture() const;
    SDL_Surface* getSDLSurface() const;
    Vector2i getSize() const;
    bool loaded() const;
    friend class AssetManager;
private:
    static std::vector<Texture*> unloadedTextures;
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = nullptr;
    Vector2i size{0,0};
};
void from_json(const json& j, Texture& u);
void to_json(json& j, const Texture& u);
}