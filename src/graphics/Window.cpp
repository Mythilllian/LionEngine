#include "graphics/Window.hpp"

namespace GameEngine {
Window::Window(Vector2i size, std::string name, Uint32 flags) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, flags);
}
Window::~Window() {
    SDL_DestroyWindow(window);
}
SDL_Window* Window::getSDLWindow() const {
    return window;
}
void Window::maximize() {
    SDL_MaximizeWindow(window);
}
void Window::minimize() {
    SDL_MinimizeWindow(window);
}
void Window::setFullscreen(bool fullscreen) {
    if (fullscreen) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    } else {
        SDL_SetWindowFullscreen(window, 0);
    }
}
void Window::setBorderered(bool bordered) {
    SDL_SetWindowBordered(window, bordered ? SDL_TRUE : SDL_FALSE);
}
void Window::setResizable(bool resizable) {
    SDL_SetWindowResizable(window, resizable ? SDL_TRUE : SDL_FALSE);
}
Vector2i Window::getSize() const {
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    return Vector2(width, height);
}
Vector2i Window::getPosition() const {
    int x, y;
    SDL_GetWindowPosition(window, &x, &y);
    return Vector2i(x, y);
}
void Window::setSize(int width, int height) {
    SDL_SetWindowSize(window, width, height);
}
void Window::setPosition(int x, int y) {
    SDL_SetWindowPosition(window, x, y);
}
void Window::setTitle(const std::string& title) {
    SDL_SetWindowTitle(window, title.c_str());
}
void Window::showWindow() {
    SDL_ShowWindow(window);
}
void Window::hideWindow() {
    SDL_HideWindow(window);
}
void Window::setIcon(Texture& texture) {
    SDL_SetWindowIcon(window, texture.getSDLSurface());
}
}