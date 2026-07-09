#include "graphics/Animation.hpp"

namespace GameEngine {
Animation::Animation(int frameWidth, int frameHeight, int frameCount, float frameDuration, Color tintColor)
        : Sprite(tintColor), texture(nullptr), frameSize(frameWidth, frameHeight), frameCount(frameCount), frameDuration(frameDuration), currentFrame(0) {}
Animation::Animation(Texture* texture, int frameWidth, int frameHeight, int frameCount, float frameDuration, Color tintColor)
        : Sprite(tintColor), texture(texture), frameSize(frameWidth, frameHeight), frameCount(frameCount), frameDuration(frameDuration), currentFrame(0) {}
Animation::Animation(Vector2i frameSize, int frameCount, float frameDuration, Color tintColor)
        : Sprite(tintColor), texture(nullptr), frameSize(frameSize), frameCount(frameCount), frameDuration(frameDuration), currentFrame(0) {}
Animation::Animation(Texture* texture, Vector2i frameSize, int frameCount, float frameDuration, Color tintColor)
        : Sprite(tintColor), texture(texture), frameSize(frameSize), frameCount(frameCount), frameDuration(frameDuration), currentFrame(0) {}
void Animation::draw(Renderer* renderer, float x, float y, float width) {
    if (playing) {
        float deltaTime = Time::deltaTime();
        float time = deltaTime + runoffTime;
        while(time >= frameDuration) {
            advanceFrame();
            runoffTime -= frameDuration;
            time -= frameDuration;
        }
        runoffTime += deltaTime;
    }

    if (!visible) return;
    if (!texture) {
        printf("Sprite draw failed: No texture loaded.\n");
        return;
    }

    SDL_Rect srcRect;
    srcRect.x = (currentFrame % (frameCount)) * frameSize.x;
    srcRect.y = 0;
    srcRect.w = frameSize.x;
    srcRect.h = frameSize.y;

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = width;
    dstRect.h = static_cast<int>(width * (static_cast<float>(texture->getSize().y) / texture->getSize().x)); // maintain aspect ratio

    SDL_SetTextureBlendMode(texture->getSDLTexture(), SDL_BLENDMODE_BLEND);
    if(tint.a != 255) {
        SDL_SetTextureAlphaMod(texture->getSDLTexture(), tint.a);
    }
    SDL_SetTextureColorMod(texture->getSDLTexture(), tint.r, tint.g, tint.b);
    SDL_RenderCopy(renderer->getSDLRenderer(), texture->getSDLTexture(), &srcRect, &dstRect);
}
void Animation::play() {
    playing = true;
}
void Animation::pause() {
    playing = false;
}
void Animation::stop() {
    playing = false;
    currentFrame = 0;
}
void Animation::restart() {
    currentFrame = 0;
    playing = true;
}
void Animation::advanceFrame() {
    if (currentFrame >= frameCount - 1) {
        currentFrame = 0;
    } else {
        currentFrame++;
    }
}
}