//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Renderer.h"
#include "../Level/LevelScene.h"
#include "raylib.h"

Renderer::Renderer() = default;

void Renderer::RenderBackground() {
    // Get the TextureManager instance and retrieve the BACKGROUND_TEXTURE from it
    GameTexture background = TextureManager::GetInstance()->GetTexture(BACKGROUND_TEXTURE);

    // Render the background.texture across the full screen's dimensions
    DrawTexturePro(background.texture, background.rect,
                   Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   Vector2{0, 0}, 0, WHITE);
}

void Renderer::Draw(const std::vector<GameObject *> &otherObjects, const std::vector<Player *> &players,
                    const std::vector<Monster *> &monsters, std::vector<Platform *> &platforms) {
    BeginDrawing(); // Setup canvas (framebuffer) to start drawing

    // Render the background
    RenderBackground();
    DrawFPS(100, 100);

    // For each object in each std::vector of GameObjects, call Draw on the object
    for (const auto& obj : players) {
        obj->Draw(); // <-- All GameObjects implement a Draw call
    }
    for (const auto& obj : monsters) {
        obj->Draw(); //
    }
    for (const auto& obj : platforms) {
        obj->Draw(); //
    }
    for (const auto& obj : otherObjects) {
        obj->Draw(); //
    }
    EndDrawing(); // End canvas drawing and swap buffers (double buffering)

}

Renderer::~Renderer() = default;
