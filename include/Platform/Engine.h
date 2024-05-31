//
// Created by ben on 5/28/24.
//

#ifndef PLATFORMER_ENGINE_H
#define PLATFORMER_ENGINE_H


#include <vector>

#include "Renderer.h"
#include "../Game/Level/Level.h"


/*
 * The Engine class is responsible for starting the game, loading the game levels, and
 * contains the main game loop, which takes ownership of a GameStateManager to draw the gameState
*/
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
