//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Renderer.h"
#include "Window.h"
#include "../Level/LevelScene.h"
#include "raylib.h"


Renderer::Renderer() : window(Window::GetInstance()) {};

void Renderer::Draw(const std::vector<GameObject*>& objects) {

    BeginDrawing();

    ClearBackground(SKYBLUE);

    for (const auto& obj : objects) {
        obj->Draw(); // Assume GameObject has a virtual Draw method
    }

    DrawRectangle(0, GetScreenHeight() - 100, GetScreenWidth(), 100, DARKBROWN);

    EndDrawing();
}