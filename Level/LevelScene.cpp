//
// Created by ben on 5/16/24.
//

#include "LevelScene.h"
#include "../Renderer/Renderer.h"

LevelScene::LevelScene() = default;

void LevelScene::Update() {
    // Update game logic, like moving the player or checking collisions
    for (auto& obj : gameObjects_) {
        obj->Update(); // Assume GameObject has an Update method
    }
}

void LevelScene::Draw(Renderer& renderer) {
    renderer.Draw(gameObjects_); // Pass all game objects to the renderer for drawing
}

// Example of adding objects to the scene
void LevelScene::AddObject(GameObject* obj) {
    gameObjects_.push_back(obj);
}