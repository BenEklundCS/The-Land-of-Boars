//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVEL_H
#define PLATFORMER_LEVEL_H

#include <memory>
#include "../Renderer/Window.h"
#include "../Renderer/Renderer.h"
#include "../Entities/Player.h"
#include "LevelScene.h"


class Level {
protected:
    std::unique_ptr<Player> player;
    Renderer renderer;
public:
public:
    virtual void Init();
    virtual void Run();
};


#endif //PLATFORMER_LEVEL_H
