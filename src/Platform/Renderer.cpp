//
// Created by ben on 5/16/24.
//

#include "../../include/Platform/Renderer.h"
#include "raylib.h"


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
                   Rectangle{backgroundPosition.x, backgroundPosition.y,(float)GetScreenWidth(), (float)GetScreenHeight()},
                   Vector2{0, 0}, 0, WHITE);
}

void Renderer::RenderFPS(Camera2D camera) {
    int offset = 20;
    DrawFPS((int)camera.target.x - GetScreenWidth()/2 + offset, (int)camera.target.y - GetScreenHeight()/2 + offset);
}
#pragma endregion

// Draw all game objects
void Renderer::Draw(GameStateManager* gameState) {

    Camera2D camera = gameState->GetCamera();

    BeginMode2D(camera);
    // Render the background
    RenderBackground(camera);
    // Render FPS
    RenderFPS(camera);

    // For each object in each std::vector of GameObjects, call Draw on the object

    for (const auto& object : gameState->GetAllObjects()) {
        object->Draw(); // <-- All GameObjects implement a Draw call
        // Draw object hitboxes

        Rectangle redBox = object->GetRect();
        DrawRectangleLines((int)redBox.x, (int)redBox.y, (int)redBox.width, (int)redBox.height, RED);

    }

    EndMode2D();
}

Renderer::~Renderer() = default;
