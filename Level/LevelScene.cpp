//
// Created by ben on 5/16/24.
//

#include "LevelScene.h"
#include "../Renderer/Renderer.h"

LevelScene::LevelScene(Player* player) {
    this->player_ = player;
}

void LevelScene::Update() {
    // Update game logic, like moving the player or checking collisions
    for (auto& obj : gameObjects_) {
        obj->Update(); // GameObjects must implement an Update() method, call it here
        // Handle player collisions
        if (obj != player_) {
            obj->CollideWithPlayer(player_);
        }
    }
}

void LevelScene::Draw(Renderer& renderer) {
    Renderer::Draw(gameObjects_); // Pass all game objects to the renderer for drawing
}

// Example of adding objects to the scene
void LevelScene::AddObject(GameObject* obj) {
    gameObjects_.push_back(obj);
}

LevelScene::~LevelScene() = default;