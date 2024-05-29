//
// Created by ben on 5/16/24.
//

#include "LevelScene.h"
#include "../Renderer/Renderer.h"

LevelScene::LevelScene() : grid_(GetScreenWidth(), GetScreenHeight(), 10, 10) {}

bool LevelScene::levelOver = false;

void LevelScene::Update() {
    // Update all game objects and handle collisions
    for (auto& player : players_) {
        player->Update();
        for (auto& platform : platforms_) {
            player->PlatformCollision(platform);
        }
    }
    for (auto& monster : monsters_) {
        monster->Update();
        for (auto& player : players_) {
            monster->CollideWithPlayer(player);
        }
        for (auto& platform : platforms_) {
            monster->PlatformCollision(platform);
        }
    }
}

void LevelScene::Draw() {
    Renderer::Draw(otherObjects_, players_, monsters_, platforms_); // Pass all game objects to the renderer for drawing
}

// Example of adding objects to the scene
void LevelScene::AddObject(GameObject* obj) {
    if (obj->type_ == PLAYER) {
        players_.push_back(dynamic_cast<Player*>(obj));
    }
    else if (obj->type_ == MONSTER) {
        monsters_.push_back(dynamic_cast<Monster*>(obj));
    }
    else if (obj->type_ == PLATFORM) {
        platforms_.push_back(dynamic_cast<Platform*>(obj));
    }
    else {
        otherObjects_.push_back(obj);
    }
}

void LevelScene::StartScene() {
    while (!WindowShouldClose() && !levelOver) {
        Update();
        if (IsLevelOver()) {
            break;
        }
        Draw();
    }
}

bool LevelScene::IsLevelOver() {
    return levelOver;
}

void LevelScene::SetLevelOver() {
    levelOver = true;
}

LevelScene::~LevelScene() = default;