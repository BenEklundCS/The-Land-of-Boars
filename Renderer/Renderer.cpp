//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Renderer.h"
#include "Window.h"
#include "../Level/LevelScene.h"
#include "raylib.h"
#include "TextureManager.h"


Renderer::Renderer() {

}

void Renderer::Draw(const std::vector<GameObject*>& objects) {

    BeginDrawing();

    DrawTexturePro(TextureManager::GetTexture("backgroundTexture"), TextureManager::GetRect("backgroundRect"),
                   Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   Vector2{0, 0}, 0, WHITE);

    for (const auto& obj : objects) {
        obj->Draw(); // Assume GameObject has a virtual Draw method
    }

    EndDrawing();

}