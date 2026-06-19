#pragma once
#include "math/Vector2.hpp"

namespace GameEngine {
class Input {
public:
    static bool isKeyPressed(int key);
    static bool isKeyReleased(int key);
    static bool isMouseButtonPressed(int button);
    static bool isMouseButtonReleased(int button);
    static float getMouseX();
    static float getMouseY();
    static Vector2 getMousePosition();
};
}