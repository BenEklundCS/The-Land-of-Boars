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

    // Set up the game for rendering

    // Assume only one level for simplicity
    const auto& level = levels[0];
    const auto gameState = level->GetGameState();
    gameState->InitCamera();

    // Initialize game input
    gameState->InitInput(settings.get());

    // Start the game loop
    GameLoop(gameState);
}

/**
 * @brief The main Game Loop. This function is responsible for running the game during runtime
 *        it uses the currentScreen enum to decide which scene function should be called for rendering.
 * @param scene - The current game scene to be rendered in case the currentScreen == GAME
 */
void Engine::GameLoop(GameStateManager* scene) const {
    while (!WindowShouldClose() && !scene->IsLevelOver() && !shouldExit_) {
        switch(currentScreen) {
            case TITLE:
                RenderTitleScreen();
                break;
            case GAME:
                RenderGameScreen(scene);
                break;
            case GAMEOVER:
                RenderGameOverScreen();
                break;
            default:
                return;
        }
    }
}

/**
 * @brief Helper method for creating a button and registering a callback function.
 */
void Engine::CreateStartButton() {
    auto onClick = [&]() {
        TraceLog(LOG_INFO, "Start button clicked.");
        HideCursor(); // hide the cursor when the start button is clicked
        currentScreen = GAME; // switch to game screen
    };

    auto onHover = [&]() {
        startButton_->SetColor(LIGHTGRAY);
    }; // create an empty function for our onHover effect

    const auto w = GetScreenWidth();
    const auto h = GetScreenHeight();

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
void Engine::RenderTitleScreen() const {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Handle Engine input ourselves, the input manager is created later.
    InputManager::HandleEngineInput();

    // Pass the start button to be drawn to screen
    Renderer::DrawTitleScreen(startButton_.get());

    // Update the start button
    startButton_->Update();

    EndDrawing();
}

/**
 * @brief Renders the main game screen.
 *
 * Assumes only one level for simplicity.
 */
void Engine::RenderGameScreen(GameStateManager* scene) {
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
}

/**
 * @brief Renders the game over screen.
 */
void Engine::RenderGameOverScreen() {

}

/**
 * @brief Sets shouldExit_ to true causing the Engine to shut down
 */
void Engine::StopGame() {
    shouldExit_ = true;
}

/**
 * @brief Destructor for the Engine class.
 */
Engine::~Engine() = default;