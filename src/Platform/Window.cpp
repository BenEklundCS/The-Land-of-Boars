//
// Created by ben on 5/16/24.
//

#include "../../include/Platform/Window.h"
#include "raylib.h"

std::unique_ptr<Window> Window::instance = nullptr;

Window::Window() {
    InitWindow(this->windowWidth_, this->windowHeight_, WINDOW_NAME); // initialize the window based on windowWidth_ and windowHeight_
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // set window resizable such that Window::Resize is callable later on
    SetTargetFPS(60); // Set the desired frames per second
    TraceLog(LOG_INFO, "Window::Window() Started successfully."); // Log Window started successfully
}

// Window::Resize requires the FLAG_WINDOW_RESIZABLE ConfigFlag is set
void Window::Resize(int window_width, int window_height) {
    // Update windowWidth and windowHeight with the passed params
    this->windowWidth_ = window_width;
    this->windowHeight_ = window_height;
    SetWindowSize(windowWidth_, windowHeight_); // call SetWindowSize
    TraceLog(LOG_INFO, "Window::Resize() Resized."); // Log the window resize
}

// Window Singleton Pattern
Window* Window::GetInstance() {
    TraceLog(LOG_INFO, "Window::GetInstance() Invoked."); // Log
    if (instance == nullptr) {
        TraceLog(LOG_INFO, "Creating window...");
        instance = std::make_unique<Window>(); // Typical singleton stuff, but I've implemented the instance as a unique ptr
    }
    return instance.get(); // if the window already exists, simply return it
}

// On a Window destructor call, close the window
Window::~Window() {
    CloseWindow();
}



