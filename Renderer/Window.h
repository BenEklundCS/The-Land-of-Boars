//
// Created by ben on 5/16/24.
//

#ifndef PLATFORMER_WINDOW_H
#define PLATFORMER_WINDOW_H

#define DEFAULT_WINDOW_WIDTH 2560
#define DEFAULT_WINDOW_HEIGHT 1440
#define WINDOW_NAME "Platformer"

class Window {

private:
    int window_width_ = DEFAULT_WINDOW_WIDTH;
    int window_height_ = DEFAULT_WINDOW_HEIGHT;
    static Window* instance;
    Window();
public:
    void Resize(int window_width, int window_height);
    static Window* GetInstance();
    ~Window();
};

#endif //PLATFORMER_WINDOW_H
