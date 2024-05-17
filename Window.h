//
// Created by ben on 5/16/24.
//

#ifndef PLATFORMER_WINDOW_H
#define PLATFORMER_WINDOW_H

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WIN_NAME "Platformer"

class Window {
private:
    int window_width_;
    int window_height_;
public:
    Window(int window_width, int window_height);
    void Resize(int window_width, int window_height);
    int GetWindowWidth();
    int GetWindowHeight();
    void Init() const;
    ~Window();
};

#endif //PLATFORMER_WINDOW_H
