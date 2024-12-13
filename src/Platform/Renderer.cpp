//
// Created by ben on 5/16/24.
//

#include "../../include/Platform/Renderer.h"
#include "raylib.h"
#include "../../include/Game/Management/GameStateManager.h"
#include "../../include/Platform/Globals.h"


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

/**
 * @brief Renders the current FPS on the screen.
 *
 * Displays the FPS in the top-left corner of the viewport, relative to the camera position.
 *
 * @param camera The Camera2D object controlling the viewport.
 */
void Renderer::RenderFPS(Camera2D camera) {
    int offset = 20;
    DrawFPS((int)camera.target.x - GetScreenWidth()/2 + offset, (int)camera.target.y - GetScreenHeight()/2 + offset);
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
    //RenderFPS(camera);

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
        // Draw level editor stuff in level editor mode
        if (gameState->GetMode() == MODE_EDITOR)
            DrawLevelEditor();
    }
    // End rendering
    EndMode2D();
}

/**
 * @brief Draws the grid for the level editor.
 *
 * This method is currently commented out due to performance concerns but can be implemented
 * to render grid lines and tile placement for level editing.
 */
void Renderer::DrawLevelEditor() {
    // BELOW CODE IS VERY PERFORMANCE INTENSIVE
    /*
    // Get the camera
    const Camera2D camera = GameStateManager::GetInstance()->GetCamera();

    // Access the TileManager position and tile dimensions
    const auto& tiles = GameStateManager::GetInstance()->GetTiles();
    constexpr Vector2 tileManagerPosition = {0, 0};

    if (tiles.empty() || tiles[0].empty()) return; // Ensure tiles are valid

    // Tile dimensions
    constexpr float baseTileWidth = TILE_LENGTH - 6; // Adjust for tile_overlap
    constexpr float baseTileHeight = TILE_LENGTH - 6;

    // Scale dimensions
    const float tileWidth = baseTileWidth * WINDOW_SCALE_FACTOR_X;
    const float tileHeight = baseTileHeight * WINDOW_SCALE_FACTOR_Y;

    // Starting position (scaled)
    const Vector2 scaledStartPos = {
        tileManagerPosition.x * WINDOW_SCALE_FACTOR_X,
        tileManagerPosition.y * WINDOW_SCALE_FACTOR_Y
    };

    // Calculate the visible area in world coordinates
    const float startX = camera.target.x - (GetScreenWidth() / 2 / camera.zoom);
    const float startY = camera.target.y - (GetScreenHeight() / 2 / camera.zoom);
    const float endX = camera.target.x + (GetScreenWidth() / 2 / camera.zoom);
    const float endY = camera.target.y + (GetScreenHeight() / 2 / camera.zoom);

    // Snap to the nearest tile grid
    const float gridStartX = scaledStartPos.x + std::floor((startX - scaledStartPos.x) / tileWidth) * tileWidth;
    const float gridStartY = (scaledStartPos.y + std::floor((startY - scaledStartPos.y) / tileHeight) * tileHeight) - tileHeight/2;

    // Draw vertical grid lines
    for (float x = gridStartX; x <= endX; x += tileWidth) {
        DrawLine(x, startY, x, endY, SKYBLUE);
    }

    // Draw horizontal grid lines
    for (float y = gridStartY; y <= endY; y += tileHeight) {
        DrawLine(startX, y, endX, y, SKYBLUE);
    }
    */
}

/**
 * @brief Renders the title screen of the game.
 *
 * Displays a title and a prompt for the user to start the game. Uses a basic camera setup
 * and centralized text rendering for the title and subtitle.
 */
void Renderer::DrawTitleScreen() {
    Camera2D titleCamera = { 0 };
    titleCamera.target = (Vector2){ static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f };
    titleCamera.offset = (Vector2){ static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f };
    titleCamera.rotation = 0.0f;
    titleCamera.zoom = 1.0f;

    // Draw the background with camera
    RenderBackground(titleCamera);

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
    DrawText("Press SPACEBAR to begin", subtitlePosX, subtitlePosY, subtitleFontSize, WHITE);
}



Renderer::~Renderer() = default;
