//
// Created by ben on 5/16/24.
//

#include "Scene.h"
#include "../Renderer/Renderer.h"

bool Scene::levelOver = false;

// Update all game objects and handle collisions
void Scene::Update() {
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

// Draw all game objects using the Renderer
void Scene::Draw() {
    Renderer::Draw(otherObjects_, players_, monsters_, platforms_); // Pass all game objects to the renderer for drawing
}


// Add a game object to the scene
void Scene::AddObject(GameObject* obj) {
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

// Start the scene, and the scene loop until the level is over, or window should close
void Scene::StartScene() {
    while (!WindowShouldClose() && !levelOver) {
        Update();
        if (IsLevelOver()) {
            break;
        }
        Draw();
    }
}

bool Scene::IsLevelOver() {
    return levelOver;
}

void Scene::SetLevelOver() {
    levelOver = true;
}

Scene::Scene() = default;

Scene::~Scene() = default;