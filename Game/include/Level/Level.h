//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVEL_H
#define PLATFORMER_LEVEL_H

#include <memory>
#include "../Player/Player.h"
#include "Scene.h"


class Level {
protected:
    std::unique_ptr<Player> player;
public:
public:
    Level();
    virtual Scene* GetScene();
    ~Level();
};


#endif //PLATFORMER_LEVEL_H
