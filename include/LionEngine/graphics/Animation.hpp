#pragma once
#include "LionEngine/graphics/ImageSprite.hpp"
#include "LionEngine/assets/Texture.hpp"
#include "LionEngine/graphics/Renderer.hpp"
#include "LionEngine/core/Time.hpp"
#include "LionEngine/math/Vector2i.hpp"
#include <SDL.h>
#include <nlohmann/json.hpp>

namespace LionEngine {
class Animation : public ImageSprite {
public:
    Animation(int frameWidth = 0, int frameHeight = 0, int frameCount = 0, float frameDuration = 1.0f, Color tintColor = Color::WHITE);
    Animation(Texture* texture, int frameWidth = 0, int frameHeight = 0, int frameCount = 0, float frameDuration = 1.0f, Color tintColor = Color::WHITE);
    Animation(Vector2i frameSize = Vector2i(0, 0), int frameCount = 0, float frameDuration = 1.0f, Color tintColor = Color::WHITE);
    Animation(Texture* texture, Vector2i frameSize = Vector2i(0, 0), int frameCount = 0, float frameDuration = 1.0f, Color tintColor = Color::WHITE);
    void draw(Renderer* renderer, float x, float y, float width, float height) override;
    void play();
    void pause();
    void stop();
    void restart();
    void advanceFrame();
    Texture* texture;
    bool playing = false;
    Vector2i frameSize = Vector2i(0, 0);
    int frameCount = 0;
    float frameDuration = 1.0f;
private:
    float runoffTime = 0.0f;
    int currentFrame = 0;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(Animation, visible, tint, texture, frameSize, frameCount, frameDuration, playing)
}