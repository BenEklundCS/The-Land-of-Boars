//
// Created by ben on 5/28/24.
//

#ifndef PLATFORMER_ENGINE_H
#define PLATFORMER_ENGINE_H


#include <vector>
#include <memory>
#include "Renderer.h"
#include "../Platform/DebugGUI.h"
#include "../Game/Level/Level.h"

class GameStateManager;

// Engine settings dictating the behavior of the PLATFORM.
struct EngineSettings {
    // Renderer
    bool renderRedBorders = false;
    // Debugging
    bool displayDebug = false;
};


/*
 * The Engine class is responsible for starting the game, loading the game levels, and
 * contains the main game loop, which takes ownership of a GameStateManager to draw the gameState
*/
class Engine {
private:
    std::vector<std::unique_ptr<Level>> levels;
    int curr = 0;
    static std::unique_ptr<EngineSettings> settings;
    static void RenderLevelScene(GameStateManager* scene); // Start the render loop
    void LoadLevels(); // Load all the game levels
public:
    void StartGame(); // Start the game
    static EngineSettings* GetSettings() {
        return settings.get();
    }
};


#endif //PLATFORMER_ENGINE_H
