//
// Created by ben on 5/28/24.
//

#ifndef PLATFORMER_GAMEMANAGER_H
#define PLATFORMER_GAMEMANAGER_H


#include <vector>
#include "../../Game/include/Level.h"


// GameManager is responsible for managing game levels, and starting the game.
class GameManager {
private:
    std::vector<std::unique_ptr<Level>> levels;
    int curr = 0;
public:
    void StartGame();
    void LoadLevels();
};


#endif //PLATFORMER_GAMEMANAGER_H
