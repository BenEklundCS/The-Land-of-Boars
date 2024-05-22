//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Renderer.h"
#include "../Level/LevelScene.h"
#include "raylib.h"

Renderer::Renderer() = default;

// Renderer::Draw draws an arbitrary std::vector of GameObjects
void Renderer::Draw(const std::vector<GameObject*>& objects) {
    BeginDrawing(); // Setup canvas (framebuffer) to start drawing

    // Render the background
    RenderBackground();

    // For each object in the std::vector of GameObjects, call Draw on the object
    for (const auto& obj : objects) {
        obj->Draw(); // <-- All GameObjects implement a Draw call
    }
    EndDrawing(); // End canvas drawing and swap buffers (double buffering)
}

void Renderer::RenderBackground() {
    // Get the TextureManager instance and retrieve the BACKGROUND_TEXTURE from it
    GameTexture background = TextureManager::GetInstance()->GetTexture(BACKGROUND_TEXTURE);

    // Render the background.texture across the full screen's dimensions
    DrawTexturePro(background.texture, background.rect,
                   Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   Vector2{0, 0}, 0, WHITE);
}

Renderer::~Renderer() = default;
