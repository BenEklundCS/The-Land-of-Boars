//
// Created by ben on 5/16/24.
//

#include "../../include/Platform/Window.h"
#include "raylib.h"
#include "../../include/Platform/Globals.h"

// Define the static instance of the Window singleton
std::unique_ptr<Window> Window::instance = nullptr;

/**
 * @brief Constructor for the Window class.
 *
 * Initializes the Raylib window, audio device, and scaling factors.
 * Sets the window to be resizable, disables the default ESC behavior, and sets a target FPS.
 */
Window::Window() {
    InitWindow(this->windowWidth_, this->windowHeight_, WINDOW_NAME); // initialize the window based on windowWidth_ and windowHeight_
    InitAudioDevice();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // set window resizable such that Window::Resize is callable later on
    //ToggleFullscreen();
    SetTargetFPS(60); // Set the desired frames per second
    SetExitKey(0);  // Disable default ESC behavior
    InitScaling(); // Initialize the scaling factors
    TraceLog(LOG_INFO, "Window::Window() Started successfully."); // Log Window started successfully
}

/**
 * @brief Resizes the window to the given dimensions.
 *
 * Updates the internal width and height of the window, applies the changes to Raylib,
 * and recalculates the scaling factors.
 *
 * @param window_width The new width of the window.
 * @param window_height The new height of the window.
 */
void Window::Resize(const int window_width, const int window_height) {
    // Update windowWidth and windowHeight with the passed params
    this->windowWidth_ = window_width;
    this->windowHeight_ = window_height;
    SetWindowSize(windowWidth_, windowHeight_); // call SetWindowSize
    InitScaling(); // Initialize the scaling factors
    TraceLog(LOG_INFO, "Window::Resize() Resized."); // Log the window resize
}

/**
 * @brief Singleton pattern implementation to retrieve the Window instance.
 *
 * Creates a new instance of the Window class if it doesn't already exist. Otherwise,
 * it returns the existing instance.
 *
 * @return Window* Pointer to the single Window instance.
 */
Window* Window::GetInstance() {
    TraceLog(LOG_INFO, "Window::GetInstance() Invoked."); // Log
    if (instance == nullptr) {
        TraceLog(LOG_INFO, "Creating window...");
        instance = std::make_unique<Window>(); // Typical singleton stuff, but I've implemented the instance as a unique ptr
    }
    return instance.get(); // if the window already exists, simply return it
}

/**
 * @brief Initializes scaling factors for the window.
 *
 * Calculates scaling factors based on the current screen dimensions relative to
 * the base resolution, as well as their inverses.
 */
void Window::InitScaling() {
    // Initialize the scaling factors
    WINDOW_SCALE_FACTOR_X = static_cast<float>(GetScreenWidth()) / BASE_SCREEN_WIDTH; // Set the window scale factor x
    WINDOW_SCALE_FACTOR_Y = static_cast<float>(GetScreenHeight()) / BASE_SCREEN_HEIGHT; // Set the window scale factor y
    // Inverses
    INVERSE_WINDOW_SCALE_FACTOR_X = BASE_SCREEN_WIDTH / static_cast<float>(GetScreenWidth()); // Set the window scale factor x
    INVERSE_WINDOW_SCALE_FACTOR_Y = BASE_SCREEN_HEIGHT / static_cast<float>(GetScreenHeight()); // Set the window scale factor y
}

/**
 * @brief Destructor for the Window class.
 *
 * Closes the Raylib window when the singleton instance is destroyed.
 */
Window::~Window() {
    CloseWindow();
}



