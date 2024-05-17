//
// Created by ben on 5/16/24.
//

#include "Window.h"
#include "raylib.h"

Window::Window(int window_width, int window_height) {
    Resize(window_width, window_height);
    Init();
}

void Window::Init() const {
    InitWindow(this->window_width_, this->window_height_, WIN_NAME);
}

void Window::Resize(int window_width, int window_height) {
    this->window_width_ = window_width;
    this->window_height_ = window_height;
}

int Window::GetWindowHeight() {
    return window_height_;
}

int Window::GetWindowWidth() {
    return window_width_;
}

Window::~Window() {
    CloseWindow();
}

