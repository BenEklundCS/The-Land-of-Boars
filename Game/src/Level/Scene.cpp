//
// Created by ben on 5/16/24.
//

#include "../../include/Level/Scene.h"
#include "../../../Platform/include/Renderer.h"

Scene::Scene() = default;

bool Scene::levelOver = false;

// Update all game objects and handle collisions
void Scene::Update() {
    // Update the camera
    UpdateCamera();
    // Update all game objects and handle collisions
    UpdatePlayers();
    UpdateMonsters();
}

// Update all players in the scene by iterating over the players, calling update, and then checking for collisions
void Scene::UpdatePlayers() {
    for (auto& player : players_) {
        player->Update();
        // Iterate over the platforms to check for collisions
        for (auto& platform : platforms_) {
            player->PlatformCollision(platform);
        }
        // Iterate over any other objects to check for collisions (especially TILEs)
        for (auto& other : otherObjects_) {
            if (other->type_ == TILE) {
                player->PlatformCollision(other);
            }
        }
    }
}

// Update all players in the scene by iterating over the monsters, calling update, and then checking for collisions
void Scene::UpdateMonsters() {
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

// Init the camera
void Scene::InitCamera() {
    Player* player1 = players_.at(0);
    camera.target = (Vector2){ player1->GetPosition().x + 20.0f, player1->GetPosition().y + 20.0f };
    camera.offset = (Vector2){ (float)GetScreenWidth()/2.0f, (float)GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

// Update the camera
void Scene::UpdateCamera() {
    Player* player1 = players_.at(0);
    camera.target = (Vector2){ player1->GetPosition().x + 20, player1->GetPosition().y + 20 };
}

bool Scene::IsLevelOver() {
    return levelOver;
}

void Scene::SetLevelOver() {
    levelOver = true;
}

Camera2D Scene::GetCamera() {
    return camera;
}

std::vector<GameObject*> Scene::GetAllObjects() {
    std::vector<GameObject*> allObjects;
    allObjects.insert(allObjects.end(), players_.begin(), players_.end());
    allObjects.insert(allObjects.end(), monsters_.begin(), monsters_.end());
    allObjects.insert(allObjects.end(), platforms_.begin(), platforms_.end());
    allObjects.insert(allObjects.end(), otherObjects_.begin(), otherObjects_.end());
    return allObjects;
}

Scene::~Scene() {
    for (auto player : players_) {
        delete player;
    }
    for (auto monster : monsters_) {
        delete monster;
    }
    for (auto platform : platforms_) {
        delete platform;
    }
    for (auto object : otherObjects_) {
        delete object;
    }
    players_.clear();
    monsters_.clear();
    platforms_.clear();
    otherObjects_.clear();
}