#pragma once
#include "math/Vector2.hpp"
#include "input/KeyCode.hpp"
#include <SDL.h>

namespace GameEngine {
class Input {
public:
    static void update();
    static bool isKeyJustPressed(KeyCode key);
    static bool isKeyJustReleased(KeyCode key);
    static bool isKeyDown(KeyCode key);
    static bool isKeyReleased(KeyCode key);
    static Vector2 getMousePosition();
private:
    static bool currentKeys[SDL_NUM_SCANCODES];
    static bool previousKeys[SDL_NUM_SCANCODES];
};
}