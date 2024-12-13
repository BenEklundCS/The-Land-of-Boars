//
// Created by ben on 5/28/24.
//

#include "../../include/Platform/Engine.h"
#include "../../include/Game/Level/LevelOne.h"
#include <stdexcept>

/**
 * @brief Default constructor for the Engine class.
 */
Engine::Engine() = default;


// Static member initialization
std::unique_ptr<EngineSettings> Engine::settings = nullptr;
bool Engine::shouldExit = false;

/**
 * @brief Load all game levels into the engine.
 *
 * Currently, only LevelOne is implemented. Additional levels can be added in the future.
 */
void Engine::LoadLevels() {
    TraceLog(LOG_INFO, "Engine loading levels...");
    auto levelOne = std::make_unique<LevelOne>();
    // auto levelTwo =
    // auto LevelThree =
    // ...
    levels.push_back(std::move(levelOne));
}

/**
 * @brief Starts the game by initializing settings, loading levels, and rendering screens sequentially.
 */
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
    // Debug mode enabled
    SetTraceLogLevel(LOG_DEBUG);
    // Call screens sequentially
    RenderTitleScreen();  // Title screen
    RenderGameScreen();   // Game screen
    RenderGameOverScreen(); // Game over screen if necessary
}

/**
 * @brief Renders the title screen.
 *
 * Displays the title screen and waits for user input to transition to the game screen.
 */
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

/**
 * @brief Renders the main game screen.
 *
 * Assumes only one level for simplicity.
 */
void Engine::RenderGameScreen() const {
    if (!shouldExit) {
        TraceLog(LOG_INFO, "Rendering Game Screen...");

        // Assume only one level for simplicity
        auto& level = levels[0];
        auto gameState = level->GetGameState();
        gameState->InitCamera();

        // Initialize game input
        gameState->InitInput(settings.get());

        // Render the level
        RenderLevelScene(gameState);
    }
}

/**
 * @brief Renders the game over screen.
 */
void Engine::RenderGameOverScreen() {
    // Implementation for the Game Over screen
    if (!shouldExit) {
        TraceLog(LOG_INFO, "Rendering Game Over Screen...");
    }
}

/**
 * @brief Checks if the escape key is pressed to exit the game.
 */
void Engine::IfEscapeExitGame() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        TraceLog(LOG_INFO, "Escape pressed, forcefully closing application...");
        shouldExit = true;
    }
}

/**
 * @brief Renders a game level scene.
 *
 * Updates and draws the scene until the level is over or the user exits.
 *
 * @param scene Pointer to the GameStateManager for the current level.
 */
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

/**
 * @brief Destructor for the Engine class.
 */
Engine::~Engine() = default;
