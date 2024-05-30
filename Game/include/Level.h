//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVEL_H
#define PLATFORMER_LEVEL_H

#include <memory>
#include "../src/Entities/Player/Player.h"



class Level {
protected:
    std::unique_ptr<Player> player;
public:
public:
    Level();
    virtual void StartLevel();
    ~Level();
};


#endif //PLATFORMER_LEVEL_H
