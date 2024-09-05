//
// Created by ben on 5/28/24.
//

#include "../../include/Platform/Engine.h"
#include "../../include/Game/Level/LevelOne.h"
#include <stdexcept>

// Declare Engine::settings as a nullptr as it is a static member attribute of Engine
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
    // Init settings such that it is not null
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
        // Get the level's gameState
        auto gameState = level->GetGameState();
        // Init the game camera
        gameState->InitCamera();
        // init the InputManager using the Engine settings
            // This allows the input manager to change settings on the fly.
        gameState->InitInput(settings.get());
        // Move the gameState to the ownership of the RenderLevelScene method, which will loop rendering the level
        RenderLevelScene(gameState);
    }
}

// Take a GameStateManager* as a parameter, initialize a renderer, and then render the scene
void Engine::RenderLevelScene(GameStateManager* gameState) {
    TraceLog(LOG_INFO, "Engine rendering a gameState...");
    // Render the level in an infinite loop
    while (!WindowShouldClose() && !gameState->IsLevelOver()) {
        // Update the game
        gameState->Update();
        // Draw the frame
        BeginDrawing();                            // Setup canvas (framebuffer) to start drawing
        Renderer::Draw(gameState, settings.get()); // Draw the scene using the renderer
        if (settings->displayDebug)                // If the debug display is enabled, display it
            DebugGUI::DrawGui(gameState);          // Draw the Debug GUI using the debug gui class
        EndDrawing();                              // End canvas drawing and swap buffers (double buffering)
        // End frame
    }
}
