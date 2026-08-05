//
// Created by ben on 5/28/24.
//

#include "../../include/Platform/Engine.h"
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
 * Levels are pure data - adding one means adding a tilemap, an entity file and
 * a line here, with no new C++.
 */
void Engine::LoadLevels() {
    TraceLog(LOG_INFO, "Engine loading levels...");
    const LevelDef defs[] = {
        {"The Clearing",   "Levels/map_level_one.txt",   "Levels/level_one.entities.txt"},
        {"The Gauntlet",   "Levels/map_level_two.txt",   "Levels/level_two.entities.txt"},
        {"The Ascent",     "Levels/map_level_three.txt", "Levels/level_three.entities.txt"},
    };
    for (const auto& def : defs) {
        levels.push_back(std::make_unique<Level>(def));
    }
    TraceLog(LOG_INFO, "Engine loaded %d levels", static_cast<int>(levels.size()));
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

    // Title screen first - it runs until the player presses Start.
    while (!WindowShouldClose() && !shouldExit_ && currentScreen == TITLE) {
        RenderTitleScreen();
    }

    // Play each level in turn. A death replays the current level rather than
    // ending the game, so levels are retryable.
    while (!WindowShouldClose() && !shouldExit_ && curr < static_cast<int>(levels.size())) {
        const LevelResult result = RunLevel(levels[curr].get());

        if (result == LEVEL_COMPLETED) {
            ++curr;
            if (curr < static_cast<int>(levels.size())) {
                if (!ShowMessageScreen("Level complete!", "Press SPACE for the next level", GREEN)) return;
            }
        }
        else if (result == LEVEL_FAILED) {
            if (!ShowMessageScreen("You died", "Press SPACE to try again", RED)) return;
        }
        else {
            return; // player quit mid-level
        }
    }

    if (!WindowShouldClose() && !shouldExit_) {
        ShowMessageScreen("You win!", "Thanks for playing - press SPACE to exit", GOLD);
    }
}

/**
 * @brief Plays a single level to completion, death, or quit.
 */
LevelResult Engine::RunLevel(const Level* level) const {
    GameStateManager* scene = level->Build();
    scene->InitCamera();
    scene->InitInput(settings.get());
    HideCursor();

    while (!WindowShouldClose() && !shouldExit_ && !scene->IsLevelOver()) {
        RenderGameScreen(scene);
    }

    ShowCursor();
    return scene->GetLevelResult();
}

/**
 * @brief Shows a full-screen message until the player continues or quits.
 */
bool Engine::ShowMessageScreen(const char* title, const char* prompt, const Color titleColor) {
    ShowCursor();
    // Wait for the key to be released first, otherwise the SPACE that ended the
    // previous screen instantly dismisses this one too.
    while (!WindowShouldClose() && IsKeyDown(KEY_SPACE)) {
        BeginDrawing();
        EndDrawing();
    }

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) return true;
        if (IsKeyPressed(KEY_ESCAPE)) return false;

        BeginDrawing();
        ClearBackground(Color{40, 30, 50, 255});

        const int titleSize = static_cast<int>(70 * WINDOW_SCALE_FACTOR_Y);
        const int promptSize = static_cast<int>(30 * WINDOW_SCALE_FACTOR_Y);
        DrawText(title, (GetScreenWidth() - MeasureText(title, titleSize)) / 2,
                 GetScreenHeight() / 2 - titleSize, titleSize, titleColor);
        DrawText(prompt, (GetScreenWidth() - MeasureText(prompt, promptSize)) / 2,
                 GetScreenHeight() / 2 + promptSize, promptSize, RAYWHITE);
        EndDrawing();
    }
    return false;
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
 * @brief Sets shouldExit_ to true causing the Engine to shut down
 */
void Engine::StopGame() {
    shouldExit_ = true;
}

/**
 * @brief Destructor for the Engine class.
 */
Engine::~Engine() = default;