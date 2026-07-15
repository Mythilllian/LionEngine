#include "LionEngine/graphics/Animation.hpp"

namespace LionEngine {
Animation::Animation(int frameWidth, int frameHeight, int frameCount, float frameDuration, Color tintColor) 
    : ImageSprite(nullptr, tintColor), frameSize(frameWidth, frameHeight), frameCount(frameCount), frameDuration(frameDuration) {}
Animation::Animation(Texture* texture, int frameWidth, int frameHeight, int frameCount, float frameDuration, Color tintColor) 
    : ImageSprite(texture, tintColor), frameSize(frameWidth, frameHeight), frameCount(frameCount), frameDuration(frameDuration) {}
Animation::Animation(Vector2i frameSize, int frameCount, float frameDuration, Color tintColor) 
    : ImageSprite(nullptr, tintColor), frameSize(frameSize), frameCount(frameCount), frameDuration(frameDuration) {}
Animation::Animation(Texture* texture, Vector2i frameSize, int frameCount, float frameDuration, Color tintColor) 
    : ImageSprite(texture, tintColor), frameSize(frameSize), frameCount(frameCount), frameDuration(frameDuration) {}
void Animation::draw(Renderer* renderer, float x, float y, float width, float height) {
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

    srcRect = Rect((currentFrame % (frameCount)) * frameSize.x, 0, frameSize.x, frameSize.y);

    renderer->drawImageSprite(this, x, y, width, height);
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