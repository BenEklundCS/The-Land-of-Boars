//
// Created by ben on 5/16/24.
//

#include "../../include/Platform/Renderer.h"
#include "../../include/Game/Entities/UI/Button.h"

#include "raylib.h"

Renderer::Renderer() = default;

#pragma region render methods

/**
 * @brief Renders the game background.
 *
 * Uses the TextureManager to retrieve the background texture and renders it across the full screen,
 * relative to the current camera position.
 *
 * @param camera The Camera2D object controlling the viewport.
 */
void Renderer::RenderBackground(const Camera2D &camera) {
    // Get the TextureManager instance and retrieve the BACKGROUND_TEXTURE from it
    auto [texture, rect] = TextureManager::GetInstance()->GetTexture(BACKGROUND_TEXTURE);
    // Get the background position from the camera
    const Vector2 backgroundPosition = { camera.target.x - static_cast<float>(GetScreenWidth()) / 2,
                                   camera.target.y - static_cast<float>(GetScreenHeight()) / 2};
    // Render the background.texture across the full screen's dimensions
    DrawTexturePro(texture, rect,
                   Rectangle{backgroundPosition.x, backgroundPosition.y,
                             static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())},
                   Vector2{0, 0}, 0, PINK);
}

/**
 * @brief Renders the current FPS on the screen.
 *
 * Displays the FPS in the top-left corner of the viewport, relative to the camera position.
 *
 * @param camera The Camera2D object controlling the viewport.
 */
void Renderer::RenderFPS(const Camera2D &camera) {
    constexpr int offset = 100;
    DrawFPS(static_cast<int>(camera.target.x) + GetScreenWidth()/2 - offset, static_cast<int>(camera.target.y) - GetScreenHeight()/2 + offset);
}
#pragma endregion

/**
 * @brief Draws all game objects within the current game state.
 *
 * Iterates through all game objects managed by the GameStateManager and calls their respective
 * `Draw` methods. Optionally renders debug information, such as red hitbox borders, if enabled.
 *
 * @param gameState Pointer to the current GameStateManager instance.
 * @param settings Pointer to the EngineSettings object controlling rendering options.
 */
void Renderer::Draw(GameStateManager* gameState, const EngineSettings* settings) {
    // Get the camera
    const Camera2D camera = gameState->GetCamera();
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
            auto [x, y, width, height] = object->GetRect();
            DrawRectangleLines(
                static_cast<int>(x),
                static_cast<int>(y),
                static_cast<int>(width),
                static_cast<int>(height),
                RED
            );
        }
    }
    // End rendering
    EndMode2D();
}

// Helper function for DrawTitleScreen to collapse all this text drawing math/code into a function
void Renderer::DrawTitleText() {
    // Scale font sizes
    const int titleFontSize = static_cast<int>(75 * WINDOW_SCALE_FACTOR_Y);
    const int subtitleFontSize = static_cast<int>(40 * WINDOW_SCALE_FACTOR_Y);

    // Measure text width to centralize it
    const int titleTextWidth = MeasureText("Welcome to The Land of Boars!", titleFontSize);
    const int subtitleTextWidth = MeasureText("Press SPACEBAR to begin", subtitleFontSize);

    // Center the title and subtitle
    const int titlePosX = (GetScreenWidth() - titleTextWidth) / 2;
    const int titlePosY = GetScreenHeight() / 2 - titleFontSize; // Slightly above center
    const int subtitlePosX = (GetScreenWidth() - subtitleTextWidth) / 2;
    const int subtitlePosY = (GetScreenHeight() / 2) + subtitleFontSize; // Slightly below center

    // Draw the title and subtitle text with centralized positions and scaled font sizes
    DrawText("Welcome to The Land of Boars!", titlePosX, titlePosY, titleFontSize, WHITE);
    DrawText("Click START GAME to begin", subtitlePosX, subtitlePosY, subtitleFontSize, WHITE);
}

void Renderer::DrawTitleButton() {

}

/**
 * @brief Renders the title screen of the game.
 *
 * Displays a title and a prompt for the user to start the game. Uses a basic camera setup
 * and centralized text rendering for the title and subtitle.
 */
void Renderer::DrawTitleScreen(Button* startButton) {
    Camera2D titleCamera = { 0 };
    titleCamera.target = (Vector2){ static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f };
    titleCamera.offset = (Vector2){ static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f };
    titleCamera.rotation = 0.0f;
    titleCamera.zoom = 1.0f;

    // Draw the background with camera
    RenderBackground(titleCamera);

    DrawTitleText();

    startButton->Draw();
}



Renderer::~Renderer() = default;
