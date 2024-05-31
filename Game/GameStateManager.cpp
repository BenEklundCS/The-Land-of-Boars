//
// Created by ben on 5/16/24.
//

#include "include/GameStateManager.h"
#include "../Platform/include/Renderer.h"

GameStateManager::GameStateManager() = default;

// Update all game objects and handle collisions
void GameStateManager::Update() {
    // Update the camera
    UpdateCamera();
    // Update all game objects and handle collisions
    UpdatePlayers(); // update Players
    UpdateMonsters(); // update Monsters
}

// Update all players in the scene by iterating over the players, calling update, and then checking for collisions
void GameStateManager::UpdatePlayers() {
    for (auto& player : players_) {
        player->Update();
        // Iterate over the platforms to check for collisions
        for (auto& platform : platforms_) {
            player->PlatformCollision(platform.get());
        }
        // Iterate over any other objects to check for collisions (especially TILEs)
        for (auto& other : otherObjects_) {
            if (other->type_ == TILE) {
                player->PlatformCollision(other.get());
            }
        }
    }
}

// Update all players in the scene by iterating over the monsters, calling update, and then checking for collisions
void GameStateManager::UpdateMonsters() {
    for (auto& monster : monsters_) {
        monster->Update();
        for (auto& player : players_) {
            monster->CollideWithPlayer(player.get());
        }
        for (auto& platform : platforms_) {
            monster->PlatformCollision(platform.get());
        }
    }
}

// Add a game object to the scene
void GameStateManager::AddObject(std::unique_ptr<GameObject> obj) {
    if (obj->type_ == PLAYER) {
        players_.push_back(std::unique_ptr<Player>(dynamic_cast<Player*>(obj.release())));
    }
    else if (obj->type_ == MONSTER) {
        monsters_.push_back(std::unique_ptr<Monster>(dynamic_cast<Monster*>(obj.release())));
    }
    else if (obj->type_ == PLATFORM) {
        platforms_.push_back(std::unique_ptr<Platform>(dynamic_cast<Platform*>(obj.release())));
    }
    else {
        otherObjects_.push_back(std::move(obj));
    }
}

// Init the camera
void GameStateManager::InitCamera() {
    Player* player1 = players_.at(0).get();
    camera.target = (Vector2){ player1->GetPosition().x + 20.0f, player1->GetPosition().y + 20.0f };
    camera.offset = (Vector2){ (float)GetScreenWidth()/2.0f, (float)GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

// Update the camera
void GameStateManager::UpdateCamera() {
    Player* player1 = players_.at(0).get();
    camera.target = (Vector2){ player1->GetPosition().x + 20, player1->GetPosition().y + 20 };
}

bool GameStateManager::IsLevelOver() const {
    return levelOver;
}

void GameStateManager::SetLevelOver() {
    levelOver = true;
}

Camera2D GameStateManager::GetCamera() {
    return camera;
}

std::vector<GameObject*> GameStateManager::GetAllObjects() {
    std::vector<GameObject*> allObjects;
    for (const auto& player : players_) allObjects.push_back(player.get());
    for (const auto& monster : monsters_) allObjects.push_back(monster.get());
    for (const auto& platform : platforms_) allObjects.push_back(platform.get());
    for (const auto& other : otherObjects_) allObjects.push_back(other.get());
    return allObjects;
}

GameStateManager::~GameStateManager() {
    players_.clear();
    monsters_.clear();
    platforms_.clear();
    otherObjects_.clear();
}