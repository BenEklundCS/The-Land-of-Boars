//
// Created by ben on 5/16/24.
//

#include "../../include/Platform/Renderer.h"
#include "raylib.h"
#include "../../include/Game/Management/GameStateManager.h"
#include "../../include/Platform/Globals.h"


Renderer::Renderer() = default;

#pragma region render methods
// Render the game background
void Renderer::RenderBackground(Camera2D camera) {
    // Get the TextureManager instance and retrieve the BACKGROUND_TEXTURE from it
    GameTexture background = TextureManager::GetInstance()->GetTexture(BACKGROUND_TEXTURE);
    // Get the background position from the camera
    Vector2 backgroundPosition = { camera.target.x - (float)GetScreenWidth() / 2, camera.target.y - (float)GetScreenHeight() / 2 };
    // Render the background.texture across the full screen's dimensions
    DrawTexturePro(background.texture, background.rect,
                   Rectangle{backgroundPosition.x, backgroundPosition.y, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   Vector2{0, 0}, 0, PINK);
}

void Renderer::RenderFPS(Camera2D camera) {
    int offset = 20;
    DrawFPS((int)camera.target.x - GetScreenWidth()/2 + offset, (int)camera.target.y - GetScreenHeight()/2 + offset);
}
#pragma endregion

// Draw all game objects
void Renderer::Draw(GameStateManager* gameState, EngineSettings* settings) {
    // Get the camera
    Camera2D camera = gameState->GetCamera();
    // Begin 2D rendering mode
    BeginMode2D(camera);
    // Render the background
    RenderBackground(camera);
    // Render FPS
    RenderFPS(camera);

    // For each object in each std::vector of GameObjects, call Draw on the object
    for (const auto& object : gameState->GetAllObjects()) {
        object->Draw(); // <-- All GameObjects implement a Draw call
        // Draw object hitboxes
        if (settings->renderRedBorders) {
            Rectangle redBox = object->GetRect();
            DrawRectangleLines((int)redBox.x, (int)redBox.y, (int)redBox.width, (int)redBox.height, RED);
        }
    }
    // End rendering
    EndMode2D();
}

void Renderer::DrawTitleScreen() {
    Camera2D titleCamera = { 0 };
    titleCamera.target = (Vector2){ static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f };
    titleCamera.offset = (Vector2){ static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f };
    titleCamera.rotation = 0.0f;
    titleCamera.zoom = 1.0f;

    // Draw the background with camera
    RenderBackground(titleCamera);

    // Scale font sizes
    int titleFontSize = static_cast<int>(75 * WINDOW_SCALE_FACTOR_Y);
    int subtitleFontSize = static_cast<int>(40 * WINDOW_SCALE_FACTOR_Y);

    // Measure text width to centralize it
    int titleTextWidth = MeasureText("Welcome to The Land of Boars!", titleFontSize);
    int subtitleTextWidth = MeasureText("Press SPACEBAR to begin", subtitleFontSize);

    // Center the title and subtitle
    float titlePosX = (GetScreenWidth() - titleTextWidth) / 2.0f;
    float titlePosY = (GetScreenHeight() / 2.0f) - (titleFontSize * 1.5f); // Slightly above center
    float subtitlePosX = (GetScreenWidth() - subtitleTextWidth) / 2.0f;
    float subtitlePosY = (GetScreenHeight() / 2.0f) + (subtitleFontSize * 1.5f); // Slightly below center

    // Draw the title and subtitle text with centralized positions and scaled font sizes
    DrawText("Welcome to The Land of Boars!", titlePosX, titlePosY, titleFontSize, WHITE);
    DrawText("Press SPACEBAR to begin", subtitlePosX, subtitlePosY, subtitleFontSize, WHITE);
}



Renderer::~Renderer() = default;
