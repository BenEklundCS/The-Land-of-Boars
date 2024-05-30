//
// Created by ben on 5/16/24.
//

#include "../include/Renderer.h"
#include "raylib.h"

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
void Renderer::Draw(Scene* scene) {
    BeginDrawing(); // Setup canvas (framebuffer) to start drawing
    ClearBackground(RAYWHITE);
    BeginMode2D(scene->GetCamera());
    // Render the background
    RenderBackground();
    DrawFPS(100, 100);

    // For each object in each std::vector of GameObjects, call Draw on the object
    for (const auto& object : scene->players_) {
        object->Draw(); // <-- All GameObjects implement a Draw call
    }
    for (const auto& object : scene->monsters_) {
        object->Draw(); // <-- All GameObjects implement a Draw call
    }
    for (const auto& object : scene->platforms_) {
        object->Draw(); // <-- All GameObjects implement a Draw call
    }
    for (const auto& object : scene->otherObjects_) {
        object->Draw(); // <-- All GameObjects implement a Draw call
    }

    EndMode2D();
    EndDrawing(); // End canvas drawing and swap buffers (double buffering)

}

Renderer::~Renderer() = default;
