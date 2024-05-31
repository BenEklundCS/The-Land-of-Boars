//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVEL_H
#define PLATFORMER_LEVEL_H

#include <memory>
#include "../Entities/Player/Player.h"
#include "../Management/GameStateManager.h"


class Level {
public:
    Level();
    virtual std::unique_ptr<GameStateManager> GetGameState();
    ~Level();
};


#endif //PLATFORMER_LEVEL_H
