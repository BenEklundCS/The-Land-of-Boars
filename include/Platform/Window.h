//
// Created by ben on 5/16/24.
//

#ifndef PLATFORMER_WINDOW_H
#define PLATFORMER_WINDOW_H

#define DEFAULT_WINDOW_WIDTH 2560
#define DEFAULT_WINDOW_HEIGHT 1440
#define WINDOW_NAME "The Land of Boars"

#include <memory>

/*
 * The Window class is a Singleton pattern responsible for managing the game window
 * We can resize the window as well with Window::Resize
 */
class Window {
private:
    // windowWidth and windowHeight are set by DEFAULT macros
    int windowWidth_ = DEFAULT_WINDOW_WIDTH;
    int windowHeight_ = DEFAULT_WINDOW_HEIGHT;
    // scaling (tied to Platform/Globals.h)
    static void InitScaling();
    // std::unique_ptr for memory management
    static std::unique_ptr<Window> instance;
public:
    Window(); // constructor
    void Resize(int window_width, int window_height); // resize the window
    static Window* GetInstance(); // get the window instance (singleton)
    ~Window(); // destructor
};

#endif //PLATFORMER_WINDOW_H
