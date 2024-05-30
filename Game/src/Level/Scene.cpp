//
// Created by ben on 5/16/24.
//

#include "../../include/Level/Scene.h"
#include "../../../Platform/include/Renderer.h"

Scene::Scene() = default;

bool Scene::levelOver = false;

// Update all game objects and handle collisions
void Scene::Update() {
    // Update all game objects and handle collisions
    UpdatePlayers();
    UpdateMonsters();
}

void Scene::UpdatePlayers() {
    for (auto& player : players_) {
        player->Update();
        for (auto& platform : platforms_) {
            player->PlatformCollision(platform);
        }
        for (auto& other : otherObjects_) {
            if (other->type_ == TILE) {
                player->PlatformCollision(other);
            }
        }
    }
}

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