//
// Created by ben on 5/28/24.
//

#include "../../include/Platform/Engine.h"
#include "../../include/Game/Level/LevelOne.h"

// Load all the levels for the game
void Engine::LoadLevels() {
    auto levelOne = std::make_unique<LevelOne>();
    // auto levelTwo =
    // auto LevelThree =
    // ...
    levels.push_back(std::move(levelOne));
}

// Start the game by loading the levels, then playing them in sequence
void Engine::StartGame() {
    // Get the window
    Window* window = Window::GetInstance();
    // Load all the levels
    LoadLevels();
    // Start each level
    for (auto& level : levels) {
        auto gameState = level->GetGameState();
        gameState->InitCamera();
        RenderLevelScene(std::move(gameState));
    }
}

// Take a GameStateManager* as a parameter, initialize a renderer, and then render the scene
void Engine::RenderLevelScene(std::unique_ptr<GameStateManager> gameState) {
    while (!WindowShouldClose() && !gameState->IsLevelOver()) {
        gameState->Update();        // Update the scene in every frame
        Renderer::Draw(gameState.get());   // Draw the scene using the renderer
    }
}



