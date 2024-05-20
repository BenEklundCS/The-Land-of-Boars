//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Renderer.h"
#include "Window.h"
#include "../Level/LevelScene.h"
#include "raylib.h"
#include "../Sprites/TextureManager.h"


Renderer::Renderer() {

}

void Renderer::Draw(const std::vector<GameObject*>& objects) {

    BeginDrawing();

    GameTexture background = TextureManager::GetTexture(BACKGROUND_TEXTURE);

    DrawTexturePro(background.texture, background.rect,
                   Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                   Vector2{0, 0}, 0, WHITE);

    for (const auto& obj : objects) {
        obj->Draw(); // Assume GameObject has a virtual Draw method
    }

    EndDrawing();

}