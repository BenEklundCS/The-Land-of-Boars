//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVELONE_H
#define PLATFORMER_LEVELONE_H

#include "../Entities/Objects/Tile.h"
#include "../Entities/Monsters/Boar.h"

#include "Level.h"

// LevelOne class is a child of Level
class LevelOne : public Level {
public:
    GameStateManager* GetGameState() override;
};

#endif //PLATFORMER_LEVELONE_H
