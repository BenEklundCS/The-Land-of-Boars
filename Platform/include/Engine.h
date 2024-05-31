//
// Created by ben on 5/28/24.
//

#ifndef PLATFORMER_ENGINE_H
#define PLATFORMER_ENGINE_H


#include <vector>
#include "../../Game/include/Level/Level.h"
#include "Renderer.h"
#include "../../Game/include/GameStateManager.h"


// Engine is responsible for managing game levels, and starting the game.
class Engine {
private:
    std::vector<std::unique_ptr<Level>> levels;
    int curr = 0;
public:
    void StartGame();
    void LoadLevels();
    static void RenderLevelScene(std::unique_ptr<GameStateManager> scene);
};


#endif //PLATFORMER_ENGINE_H
