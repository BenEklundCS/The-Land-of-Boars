//
// Created by ben on 5/16/24.
//

#include "LevelScene.h"
#include "../Renderer/Renderer.h"

void LevelScene::Update() {
    // Update all game objects and handle collisions
    for (auto& obj : gameObjects_) {
        obj->Update();

        // Handle player-specific logic
        if (obj->type_ == PLAYER) {
            auto player = dynamic_cast<Player*>(obj);

            // Check collisions with platforms
            for (auto& platform : gameObjects_) {
                if (platform->type_ == PLATFORM) {
                    player->PlatformCollision(platform);
                }
            }

            // Check collisions with monsters
            for (auto& monster : gameObjects_) {
                if (monster->type_ == MONSTER) {
                    dynamic_cast<Monster*>(monster)->CollideWithPlayer(player);
                }
            }

            // Check collisions with other game objects
            for (auto& other : gameObjects_) {
                if (other != player && other->type_ != PLATFORM && other->type_ != MONSTER) {
                    other->CollideWithPlayer(player);
                }
            }
        } else if (obj->type_ == MONSTER) {
            auto monster = dynamic_cast<Monster*>(obj);

            // Check collisions with platforms
            for (auto& platform : gameObjects_) {
                if (platform->type_ == PLATFORM) {
                    monster->PlatformCollision(platform);
                }
            }
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

LevelScene::LevelScene() = default;

LevelScene::~LevelScene() = default;