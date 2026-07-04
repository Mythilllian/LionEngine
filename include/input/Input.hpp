#pragma once
#include "math/Vector2.hpp"
#include "input/KeyCode.hpp"
#include <SDL.h>
#include "core/Engine.hpp"

namespace GameEngine {
class Engine;
class Input {
public:
    static bool isKeyJustPressed(KeyCode key);
    static bool isKeyJustReleased(KeyCode key);
    static bool isKeyDown(KeyCode key);
    static bool isKeyReleased(KeyCode key);
    static bool wasQuitRequested();
    static Vector2 getMousePosition();
    friend class Engine;
private:
    static void update();
    static bool currentKeys[SDL_NUM_SCANCODES];
    static bool previousKeys[SDL_NUM_SCANCODES];
    static bool quitRequested;
};
}