//
// Created by ben on 5/28/24.
//

#include "../../include/Platform/Engine.h"
#include "../../include/Game/Level/LevelOne.h"

// Load all the levels for the game
void Engine::LoadLevels() {
    TraceLog(LOG_INFO, "Engine loading levels...");
    auto levelOne = std::make_unique<LevelOne>();
    // auto levelTwo =
    // auto LevelThree =
    // ...
    levels.push_back(std::move(levelOne));
}

// Start the game by loading the levels, then playing them in sequence
void Engine::StartGame() {
    TraceLog(LOG_INFO, "Engine starting game...");
    // Get the window
    Window* window = Window::GetInstance();
    // Load all the levels
    LoadLevels();
    // Start ImGUI
    DebugGUI::InitGui();
    // Start each level
    for (auto& level : levels) {
        auto gameState = level->GetGameState();
        gameState->InitCamera();
        gameState->InitInput();
        RenderLevelScene(std::move(gameState));
    }
}

// Take a GameStateManager* as a parameter, initialize a renderer, and then render the scene
void Engine::RenderLevelScene(std::unique_ptr<GameStateManager> gameState) {
    TraceLog(LOG_INFO, "Engine rendering a gameState...");
    // Render the level in an infinite loop
    while (!WindowShouldClose() && !gameState->IsLevelOver()) {
        // Update the game
        gameState->Update();        // Update the scene
        if (IsKeyPressed(KEY_D)) // if KEY_D is pressed
            displayDebug = !displayDebug; // Toggle the debug display

        // Draw the frame
        BeginDrawing();             // Setup canvas (framebuffer) to start drawing
            Renderer::Draw(gameState.get());    // Draw the scene using the renderer
            if (displayDebug) // If the debug display is enabled, display it
                DebugGUI::DrawGui(gameState.get());// Draw the Debug GUI using the debug gui class
        EndDrawing();               // End canvas drawing and swap buffers (double buffering)
        // End frame
    }
}



