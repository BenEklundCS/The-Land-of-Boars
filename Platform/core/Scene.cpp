//
// Created by ben on 5/16/24.
//

#include "../include/Scene.h"
#include "../include/Renderer.h"

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

// Draw all game objects using the Renderer
void Scene::Draw() {
    renderer.Draw(camera);
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
    InitCamera();
    this->renderer = Renderer(players_, monsters_, platforms_, otherObjects_);
    while (!WindowShouldClose() && !levelOver) {
        Update();
        UpdateCamera();
        if (IsLevelOver()) {
            break;
        }
        Draw();
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

Scene::~Scene() = default;