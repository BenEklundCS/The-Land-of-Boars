//
// Created by ben on 5/16/24.
//

#include "LevelScene.h"
#include "../Renderer/Renderer.h"

void LevelScene::Update() {
    // Update the players and handle collisions with platforms and monsters
    for (auto& player : players_) {
        player->Update();

        // Check collisions with platforms
        for (auto& platform : platforms_) {
            player->PlatformCollision(platform);
        }

        // Check collisions with monsters
        for (auto& monster : monsters_) {
            monster->CollideWithPlayer(player);
        }
    }

    // Update monsters and handle their collisions with platforms
    for (auto& monster : monsters_) {
        monster->Update();
        for (auto& platform : platforms_) {
            monster->PlatformCollision(platform);
        }
    }

    // Update other game objects
    for (auto& obj : otherObjects_) {
        obj->Update();
    }

    // Handle player collisions with other game objects
    for (auto& obj : otherObjects_) {
        for (auto& player : players_) {
            obj->CollideWithPlayer(player);
        }
    }
}

void LevelScene::Draw(Renderer& renderer) {
    Renderer::Draw(gameObjects_); // Pass all game objects to the renderer for drawing
}

// Example of adding objects to the scene
void LevelScene::AddObject(GameObject* obj) {
    gameObjects_.push_back(obj);
    if (obj->type_ == MONSTER) {
        monsters_.push_back(dynamic_cast<Monster*>(obj));
    } else if (obj->type_ == PLATFORM) {
        platforms_.push_back(dynamic_cast<Platform*>(obj));
    } else if (obj->type_ == PLAYER) {
        players_.push_back(dynamic_cast<Player*>(obj));
    } else {
        otherObjects_.push_back(obj);
    }
}

LevelScene::LevelScene() {

}

LevelScene::~LevelScene() = default;