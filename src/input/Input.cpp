#include "LionEngine/input/Input.hpp"
#include <iostream>

namespace LionEngine {
bool Input::currentKeys[SDL_NUM_SCANCODES] = {};
bool Input::previousKeys[SDL_NUM_SCANCODES] = {};
bool Input::quitRequested = false;
void Input::update() {
    std::copy(
        currentKeys,
        currentKeys + SDL_NUM_SCANCODES,
        previousKeys
    );

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
            currentKeys[event.key.keysym.scancode] = true;
        if (event.type == SDL_KEYUP && event.key.repeat == 0)
            currentKeys[event.key.keysym.scancode] = false;
        if (event.type == SDL_MOUSEBUTTONDOWN)
            currentKeys[event.button.button] = true;
        if (event.type == SDL_MOUSEBUTTONUP)
            currentKeys[event.button.button] = false;
        if (event.type == SDL_QUIT)
            quitRequested = true;
    }
}
bool Input::isKeyJustPressed(KeyCode key) {
    return currentKeys[static_cast<int>(key)] && !previousKeys[static_cast<int>(key)];
}
bool Input::isKeyJustReleased(KeyCode key) {
    return !currentKeys[static_cast<int>(key)] && previousKeys[static_cast<int>(key)];
}
bool Input::isKeyReleased(KeyCode key)
{
    return !currentKeys[static_cast<int>(key)];
}
bool Input::isKeyDown(KeyCode key)
{
    return currentKeys[static_cast<int>(key)];
}
bool Input::wasQuitRequested() {
    return quitRequested;
}
Vector2 Input::getMousePosition() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return Vector2(x, y);
}
}