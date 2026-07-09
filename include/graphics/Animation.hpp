#pragma once
#include "graphics/Sprite.hpp"
#include "assets/Texture.hpp"
#include "graphics/Renderer.hpp"
#include "core/Time.hpp"
#include "math/Vector2i.hpp"
#include <SDL.h>
#include <nlohmann/json.hpp>

namespace GameEngine {
class Animation : public Sprite {
public:
    Animation(int frameWidth = 0, int frameHeight = 0, int frameCount = 0, float frameDuration = 1, Color tintColor = Color::WHITE);
    Animation(Texture* texture, int frameWidth = 0, int frameHeight = 0, int frameCount = 0, float frameDuration = 1, Color tintColor = Color::WHITE);
    Animation(Vector2i frameSize = Vector2i(0, 0), int frameCount = 0, float frameDuration = 1, Color tintColor = Color::WHITE);
    Animation(Texture* texture, Vector2i frameSize = Vector2i(0, 0), int frameCount = 0, float frameDuration = 1, Color tintColor = Color::WHITE);
    void draw(Renderer* renderer, float x, float y, float width) override;
    void play();
    void pause();
    void stop();
    void restart();
    void advanceFrame();
    Texture* texture;
    bool playing = false;
    Vector2i frameSize;
    int frameCount;
    float frameDuration;
private:
    float runoffTime = 0.0f;
    int currentFrame = 0;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Animation, visible, tint, texture, frameSize, frameCount, frameDuration, playing)
}