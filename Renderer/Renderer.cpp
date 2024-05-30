//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Renderer.h"
#include "Scene.h"
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
void Renderer::Draw(Camera2D sceneCamera) {
    BeginDrawing(); // Setup canvas (framebuffer) to start drawing
    ClearBackground(RAYWHITE);
    BeginMode2D(sceneCamera);
    // Render the background
    RenderBackground();
    DrawFPS(100, 100);

    // For each object in each std::vector of GameObjects, call Draw on the object
    for (const auto& player : players_) {
        player->Draw(); // <-- All GameObjects implement a Draw call
    }
    for (const auto& monster : monsters_) {
        monster->Draw(); //
    }
    for (const auto& platform : platforms_) {
        platform->Draw(); //
    }
    for (const auto& obj : otherObjects_) {
        obj->Draw(); //
    }
    EndMode2D();
    EndDrawing(); // End canvas drawing and swap buffers (double buffering)

}

Renderer::Renderer(std::vector<Player *> &players, std::vector<Monster *> &monsters,
                   std::vector<Platform *> &platforms, std::vector<GameObject *> &other)
                   : players_(players), monsters_(monsters), platforms_(platforms), otherObjects_(other) {}


Renderer::~Renderer() = default;
