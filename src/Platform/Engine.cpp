#include "../../include/Platform/Engine.h"
#include "../../include/Game/Level/LevelOne.h"
#include <stdexcept>

std::unique_ptr<EngineSettings> Engine::settings = nullptr;
bool Engine::shouldExit = false;

void Engine::LoadLevels() {
    TraceLog(LOG_INFO, "Engine loading levels...");
    auto levelOne = std::make_unique<LevelOne>();
    levels.push_back(std::move(levelOne));
}

void Engine::StartGame() {
    settings = std::make_unique<EngineSettings>();
    TraceLog(LOG_INFO, "Engine starting game...");

    Window* window = Window::GetInstance();
    LoadLevels();
    DebugGUI::InitGui();

    RenderTitleScreen();
    if (!shouldExit) RenderGameScreen();
    if (!shouldExit) RenderGameOverScreen();

    // Clean up and close the window only once, after the main game loops
    CloseWindow();
}

void Engine::RenderTitleScreen() {
    TraceLog(LOG_INFO, "Rendering Title Screen...");
    while (!WindowShouldClose() && !shouldExit) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Renderer::DrawTitleScreen();

        if (IsKeyPressed(KEY_SPACE)) {
            currentScreen = GAME;
            break;
        }

        IfEscapeExitGame();
        EndDrawing();
    }
}

void Engine::RenderGameScreen() {
    TraceLog(LOG_INFO, "Rendering Game Screen...");

    auto& level = levels[0];
    auto gameState = level->GetGameState();
    gameState->InitCamera();
    gameState->InitInput(settings.get());

    RenderLevelScene(gameState);
}

void Engine::RenderGameOverScreen() {
    // Render Game Over screen logic
}

void Engine::IfEscapeExitGame() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        TraceLog(LOG_INFO, "Escape pressed, setting shouldExit to true...");
        shouldExit = true;
    }
}

void Engine::MaybeExitGame() {
    // Check if shouldExit is true and break out of the main game loops if so
    if (shouldExit) {
        TraceLog(LOG_INFO, "MaybeExitGame detected shouldExit is true...");
    }
}

void Engine::RenderLevelScene(GameStateManager* gameState) {
    TraceLog(LOG_INFO, "Rendering Level Scene...");
    while (!WindowShouldClose() && !gameState->IsLevelOver() && !shouldExit) {
        gameState->Update();
        BeginDrawing();
        Renderer::Draw(gameState, settings.get());
        if (settings->displayDebug)
            DebugGUI::DrawGui(gameState);

        IfEscapeExitGame();
        EndDrawing();
    }
}
