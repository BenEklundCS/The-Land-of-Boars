//
// Created by ben on 5/16/24.
//

#include "../../include/Platform/Window.h"
#include "raylib.h"
#include "../../include/Platform/Globals.h"

std::unique_ptr<Window> Window::instance = nullptr;

Window::Window() {
    InitWindow(this->windowWidth_, this->windowHeight_, WINDOW_NAME); // initialize the window based on windowWidth_ and windowHeight_
    InitAudioDevice();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // set window resizable such that Window::Resize is callable later on
    SetTargetFPS(60); // Set the desired frames per second
    SetExitKey(0);  // Disable default ESC behavior
    InitScaling(); // Initialize the scaling factors
    TraceLog(LOG_INFO, "Window::Window() Started successfully."); // Log Window started successfully
}

// Window::Resize requires the FLAG_WINDOW_RESIZABLE ConfigFlag is set
void Window::Resize(int window_width, int window_height) {
    // Update windowWidth and windowHeight with the passed params
    this->windowWidth_ = window_width;
    this->windowHeight_ = window_height;
    SetWindowSize(windowWidth_, windowHeight_); // call SetWindowSize
    InitScaling(); // Initialize the scaling factors
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

void Window::InitScaling() {
    // Initialize the scaling factors
    WINDOW_SCALE_FACTOR_X = static_cast<float>(GetScreenWidth()) / BASE_SCREEN_WIDTH; // Set the window scale factor x
    WINDOW_SCALE_FACTOR_Y = static_cast<float>(GetScreenHeight()) / BASE_SCREEN_HEIGHT; // Set the window scale factor y
    // Inverses
    INVERSE_WINDOW_SCALE_FACTOR_X = BASE_SCREEN_WIDTH / static_cast<float>(GetScreenWidth()); // Set the window scale factor x
    INVERSE_WINDOW_SCALE_FACTOR_Y = BASE_SCREEN_HEIGHT / static_cast<float>(GetScreenHeight()); // Set the window scale factor y
}

// On a Window destructor call, close the window
Window::~Window() {
    CloseWindow();
}



