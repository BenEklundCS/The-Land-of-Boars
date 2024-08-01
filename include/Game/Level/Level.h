//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVEL_H
#define PLATFORMER_LEVEL_H

#include <memory>
#include "../Entities/Player/Player.h"

class StateManager;

// A level is really a loader script for a StateManager object
class Level {
public:
    Level();
    virtual StateManager* GetGameState(); // Return a unique_ptr to a StateManager object loaded by the level
    ~Level();
};


#endif //PLATFORMER_LEVEL_H
