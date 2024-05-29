//
// Created by ben on 5/28/24.
//

#ifndef PLATFORMER_GAMEMANAGER_H
#define PLATFORMER_GAMEMANAGER_H


#include <vector>
#include "../Level/Level.h"
#include "../Level/LevelOne.h"

class GameManager {
private:
    std::vector<std::unique_ptr<Level>> levels;
    int curr = 0;
public:
    void StartGame();
    void LoadLevels();
};


#endif //PLATFORMER_GAMEMANAGER_H
