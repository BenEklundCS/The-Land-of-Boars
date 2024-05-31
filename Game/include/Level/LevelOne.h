//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVELONE_H
#define PLATFORMER_LEVELONE_H

#include "Level.h"

class LevelOne : public Level {
public:
    std::unique_ptr<GameStateManager> GetGameState() override;
};

#endif //PLATFORMER_LEVELONE_H
