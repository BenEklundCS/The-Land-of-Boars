//
// Created by ben on 5/28/24.
//

#include "../../include/Platform/Engine.h"
#include "../../include/Game/Level/LevelOne.h"
#include <exception>

std::unique_ptr<EngineSettings> Engine::settings = nullptr;

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
    settings = std::make_unique<EngineSettings>();
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
        gameState->InitInput(settings.get()); // init ur settings if you don't want them to be null
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
        // Draw the frame
        BeginDrawing();             // Setup canvas (framebuffer) to start drawing
            Renderer::Draw(gameState.get(), settings->renderRedBorders);    // Draw the scene using the renderer
            if (settings->displayDebug) // If the debug display is enabled, display it
                DebugGUI::DrawGui(gameState.get());// Draw the Debug GUI using the debug gui class
        EndDrawing();               // End canvas drawing and swap buffers (double buffering)
        // End frame
    }
}



