//
// Created by ben on 5/16/24.
//

#include "Window.h"
#include "raylib.h"

std::unique_ptr<Window> Window::instance = nullptr;

Window::Window() {
    InitWindow(this->window_width_, this->window_height_, WINDOW_NAME);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60); // Set the desired frames per second
    TraceLog(LOG_INFO, "Window::Window() Started successfully.");
}

void Window::Resize(int window_width, int window_height) {
    TraceLog(LOG_INFO, "Window::Resize() Resized.");
    this->window_width_ = window_width;
    this->window_height_ = window_height;
    SetWindowSize(window_width_, window_height_);
}

Window* Window::GetInstance() {
    TraceLog(LOG_INFO, "Window::GetInstance() Invoked.");
    if (instance == nullptr) {
        instance = std::make_unique<Window>();
    }
    return instance.get();
}

Window::~Window() = default;



