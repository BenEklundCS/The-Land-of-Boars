//
// Created by ben on 5/16/24.
//

#include "../include/Renderer.h"
#include "raylib.h"
#include "../../Game/include/Entities/GameObject.h"
#include "../../Game/include/Entities/Objects/Platform.h"
#include "../../Game/include/Entities/Monsters/Monster.h"
#include "../../Game/include/Management/GameStateManager.h"

Renderer::Renderer() = default;

// Render the game background
void Renderer::RenderBackground() {
    // Get the TextureManager instance and retrieve the BACKGROUND_TEXTURE from it
    GameTexture background = TextureManager::GetInstance()->GetTexture(BACKGROUND_TEXTURE);

    // Render the background.texture across the full screen's dimensions
    DrawTexturePro(background.texture, background.rect,
                   Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   Vector2{0, 0}, 0, WHITE);
}

// Draw all game objects
void Renderer::Draw(GameStateManager* gameState) {
    BeginDrawing(); // Setup canvas (framebuffer) to start drawing
    ClearBackground(BLACK);
    BeginMode2D(gameState->GetCamera());
    // Render the background
    RenderBackground();
    DrawFPS(100, 100);

    // For each object in each std::vector of GameObjects, call Draw on the object
    for (const auto& object : gameState->GetAllObjects()) {
        object->Draw(); // <-- All GameObjects implement a Draw call
    }

    EndMode2D();
    EndDrawing(); // End canvas drawing and swap buffers (double buffering)

}

Renderer::~Renderer() = default;
