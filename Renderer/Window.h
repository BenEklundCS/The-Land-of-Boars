//
// Created by ben on 5/16/24.
//

#ifndef PLATFORMER_WINDOW_H
#define PLATFORMER_WINDOW_H

#define WINDOW_WIDTH 2560
#define WINDOW_HEIGHT 1440
#define WINDOW_NAME "Platformer"

class Window {

private:
    int window_width_ = WINDOW_WIDTH;
    int window_height_ = WINDOW_HEIGHT;
    static Window* instance;
    Window();
public:
    void Resize(int window_width, int window_height);
    static Window* GetInstance();
    ~Window();
};

#endif //PLATFORMER_WINDOW_H
