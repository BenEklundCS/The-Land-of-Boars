//
// Created by ben on 5/28/24.
//

#include "../../include/Platform/Engine.h"
#include "../../include/Game/Level/LevelOne.h"
#include <stdexcept>

// Declare Engine::settings as a nullptr as it is a static member attribute of Engine
std::unique_ptr<EngineSettings> Engine::settings = nullptr;
bool Engine::shouldExit = false;

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
    Window::GetInstance();

    // Load all the levels
    LoadLevels();

    // Start ImGUI
    DebugGUI::InitGui();

    // Call screens sequentially
    RenderTitleScreen();  // Title screen
    RenderGameScreen();   // Game screen
    RenderGameOverScreen(); // Game over screen if necessary
}

void Engine::RenderTitleScreen() {
    TraceLog(LOG_INFO, "Rendering Title Screen...");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Renderer::DrawTitleScreen(); // Assuming this draws the title screen

        // Check for key press to exit title screen and start the game
        if (IsKeyPressed(KEY_SPACE)) {
            currentScreen = GAME;
            break; // Exit loop and return to StartGame
        }

        IfEscapeExitGame();

        EndDrawing();

        if (shouldExit) {
            break;
        }
    }
}

void Engine::RenderGameScreen() const {
    if (!shouldExit) {
        TraceLog(LOG_INFO, "Rendering Game Screen...");

        // Assume only one level for simplicity
        auto& level = levels[0];
        auto gameState = level->GetGameState();
        gameState->InitCamera();
        gameState->InitInput(settings.get());

        // Render the level
        RenderLevelScene(gameState);
    }
}

void Engine::RenderGameOverScreen() {
    // Implementation for the Game Over screen
    if (!shouldExit) {
        TraceLog(LOG_INFO, "Rendering Game Over Screen...");
    }
}

void Engine::IfEscapeExitGame() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        TraceLog(LOG_INFO, "Escape pressed, forcefully closing application...");
        shouldExit = true;
    }
}

// Take a GameStateManager* as a parameter, initialize a renderer, and then render the scene
void Engine::RenderLevelScene(GameStateManager* scene) {
    if (!shouldExit) {
        TraceLog(LOG_INFO, "Rendering Level Scene...");

        // Render the level until it's over or the window should close
        while (!WindowShouldClose() && !scene->IsLevelOver()) {
            // Update the game
            scene->Update();

            // Draw the frame
            BeginDrawing();
            Renderer::Draw(scene, settings.get()); // Draw the scene
            if (settings->displayDebug)
                DebugGUI::DrawGui(scene); // Draw the debug GUI if necessary

            IfEscapeExitGame();

            EndDrawing();

            if (shouldExit) {
                return;
            }
        }
    }
}
