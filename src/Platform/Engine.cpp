//
// Created by ben on 5/28/24.
//

#include "../../include/Platform/Engine.h"
#include "../../include/Game/Level/LevelOne.h"
#include "../../include/Game/Management/InputManager.h"
#include <stdexcept>

/**
 * @brief Default constructor for the Engine class.
 */
Engine::Engine() = default;


// Static member initialization
std::unique_ptr<EngineSettings> Engine::settings = nullptr;
bool Engine::shouldExit_ = false;

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

    // Create the start button
    CreateStartButton();

    // Start ImGUI
    GUI::InitGui();
    // Debug mode enabled
    SetTraceLogLevel(LOG_DEBUG);
    // Call screens sequentially
    RenderTitleScreen();  // Title screen
    RenderGameOverScreen(); // Game over screen if necessary
}

/**
 * @brief Helper method for creating a button and registering a callback function.
 */
void Engine::CreateStartButton() {
    auto onClick = [&]() {
        TraceLog(LOG_INFO, "Start button clicked.");
        RenderGameScreen(); // Render the Game Screen once the start button has been clicked.
    };

    auto onHover = [&]() {
        startButton_->SetColor(LIGHTGRAY);
    }; // create an empty function for our onHover effect

    auto w = GetScreenWidth();
    auto h = GetScreenHeight();

    auto position = Vector2{static_cast<float>((w)/2-(w/8)), static_cast<float>(h/2+(h/7))};
    auto dimensions = Vector2{(float)BUTTON_WIDTH, (float)BUTTON_HEIGHT};
    auto text = "Start game";

    // Create a start button for the game that will call RenderGameScreen();
    startButton_ = std::make_unique<Button>(position, dimensions, onClick, onHover, text);
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

        // Handle Engine input ourselves, the input manager is created later.
        InputManager::HandleEngineInput();

        // Update the start button
        startButton_->Update();

        // Pass the start button to be drawn to screen
        Renderer::DrawTitleScreen(startButton_.get());

        EndDrawing();

        if (shouldExit_) {
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
    if (!shouldExit_) {
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
    if (!shouldExit_) {
        TraceLog(LOG_INFO, "Rendering Game Over Screen...");
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
    if (!shouldExit_) {
        TraceLog(LOG_INFO, "Rendering Level Scene...");

        // Render the level until it's over or the window should close
        while (!WindowShouldClose() && !scene->IsLevelOver()) {
            // Update the game
            scene->Update();

            // Draw the frame
            BeginDrawing();
            Renderer::Draw(scene, settings.get()); // Draw the scene
            if (settings->displayDebug)
                GUI::DrawDebugGUI(scene); // Draw the debug GUI if necessary
            // Editor mode GUI
            if (scene->GetMode() == MODE_EDITOR)
                GUI::DrawEditorGUI();

            EndDrawing();

            if (shouldExit_) {
                return;
            }
        }
    }
}

void Engine::StopGame() {
    shouldExit_ = true;
}

/**
 * @brief Destructor for the Engine class.
 */
Engine::~Engine() = default;
