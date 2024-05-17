//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Renderer.h"
#include "Window.h"
#include "../Level/LevelScene.h"
#include "raylib.h"


Renderer::Renderer() = default;

void Renderer::Draw(const std::vector<GameObject*>& objects) {

    BeginDrawing();

    ClearBackground(SKYBLUE);

    for (const auto& obj : objects) {
        obj->Draw(); // Assume GameObject has a virtual Draw method
    }

    EndDrawing();

}