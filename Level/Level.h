//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVEL_H
#define PLATFORMER_LEVEL_H

#include "../Renderer/Window.h"
#include "../Renderer/Renderer.h"
#include "../Entities/Player.h"
#include "LevelScene.h"


class Level {
private:
    Window* window = Window::GetInstance(); // init the window with GetInstance
protected:
    Player* player;
    Renderer renderer;
public:
public:
    virtual void Init();
    virtual void Run();
    virtual void Cleanup();
};


#endif //PLATFORMER_LEVEL_H
