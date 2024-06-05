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
    // Start ImGUI
    // Start ImGUI
    TraceLog(LOG_INFO, "Setting up ImGui");
    debug_gui_.InitGui();
    TraceLog(LOG_INFO, "ImGui setup complete");
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
        BeginDrawing();             // Setup canvas (framebuffer) to start drawing
        Renderer::Draw(gameState.get());    // Draw the scene using the renderer
        debug_gui_.DrawGui(gameState.get());// Draw the Debug GUI using the debug gui class
        EndDrawing();               // End canvas drawing and swap buffers (double buffering)
    }
}



