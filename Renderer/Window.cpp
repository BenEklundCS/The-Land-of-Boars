//
// Created by ben on 5/16/24.
//

#include "Window.h"
#include "raylib.h"

Window* Window::instance = nullptr;

Window::Window() {
    InitWindow(this->window_width_, this->window_height_, WINDOW_NAME);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60); // Set the desired frames per second
}

void Window::Resize(int window_width, int window_height) {
    this->window_width_ = window_width;
    this->window_height_ = window_height;
    SetWindowSize(window_width_, window_height_);
}

Window* Window::GetInstance() {
    if (instance == nullptr) {
        instance = new Window();
    }
    return instance;
}

Window::~Window() {
    CloseWindow();
}



