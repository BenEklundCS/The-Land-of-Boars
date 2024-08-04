//
// Created by ben on 5/16/24.
//

#include "../../../include/Platform/Renderer.h"
#include "../../../include/Game/Management/InputManager.h"
#include "../../../include/Game/Management/GameStateManager.h"
#include <algorithm>

std::unique_ptr<GameStateManager> GameStateManager::instance = nullptr;

GameStateManager::GameStateManager() {
    levelOver = false;
}

// Window Singleton Pattern
GameStateManager* GameStateManager::GetInstance() {
    TraceLog(LOG_INFO, "GameStateManager::GetInstance() Invoked."); // Log
    if (instance == nullptr) {
        TraceLog(LOG_INFO, "Creating GameStateManager...");
        instance = std::make_unique<GameStateManager>(); // Typical singleton stuff, but I've implemented the instance as a unique ptr
    }
    return instance.get(); // if the window already exists, simply return it
}

#pragma region update gameState methods

// Update all game objects and handle collisions
void GameStateManager::Update() {
    // Update the camera
    UpdateCamera();
    // Update all game objects and handle collisions
    UpdatePlayers(); // update Players
    UpdatePlatforms(); // update Platforms
    // Handle user input
    inputManager_->HandleUserInput();
    UpdateMonsters(); // update Monsters
}

void GameStateManager::UpdatePlatforms() {
    #pragma omp parallel for
    for (auto& platform : platforms_) {
        platform->Update();
    }
}

// Update all players in the scene by iterating over the players, calling update, and then checking for collisions
void GameStateManager::UpdatePlayers() {
    for (auto& player : players_) {
        player->Update();
        // Iterate over the platforms to check for collisions
        #pragma omp parallel for
        for (auto& platform : platforms_) {
            player->PlatformCollision(platform.get());
        }
        // Iterate over any other objects to check for collisions (especially TILEs)
        #pragma omp parallel for // update the other objects in parallel using threads
        for (auto& other : otherObjects_) {
            player->PlatformCollision(other.get());
        }
    }
}

// Handle player and monster attacks onscreen
void GameStateManager::UpdateAttacks(Player* player) {
    // Vector to store delayed updates
    std::vector<GameObject*> toRemove;
    // Iterate over all monsters
    #pragma omp parallel for
    for (auto& monster : monsters_) {
        bool shouldBeRemoved = HandlePlayerAttack(player, monster.get());
        if (shouldBeRemoved) {
            toRemove.push_back(monster.get());
        }
    }
    // Defer deletions of monsters to avoid issues accessing them (memory exceptions!) in the loop above ^
    for (auto& obj : toRemove) {
        RemoveObject(obj);
    }
}

// Update all players in the scene by iterating over the monsters, calling update, and then checking for collisions
void GameStateManager::UpdateMonsters() {
    #pragma omp parallel for
    for (auto& monster : monsters_) {
        monster->Update();
        for (auto& player : players_) {
            monster->CollideWithPlayer(player.get());
        }
        for (auto& platform : platforms_) {
            monster->PlatformCollision(platform.get());
        }
        #pragma omp parallel for // update the other objects in parallel using threads
        for (auto& other : otherObjects_) {
            monster->PlatformCollision(other.get());
        }
    }
}

#pragma endregion

#pragma region observer-events

// GameStateManager OnNotify from Observer Pattern
void GameStateManager::OnNotify(const GameObject *entity, Events event) {
    // Player events!
    if (entity->type_ == PLAYER) {
        if (event == EVENT_PLAYER_ATTACK) {
            UpdateAttacks((Player *) entity);
        }
    }
}

#pragma endregion

#pragma region object loading/interaction

// Add a game object to the GameStateManager. The GameStateManager maintains unique_ptr ownership over Objects.
// Make sure to pass a std::unique_ptr<GameObject> to it using std::move()
// Do not add nullptr objects, undefined behavior
void GameStateManager::AddObject(std::unique_ptr<GameObject> obj) {
    allGameObjects_.push_back(obj.get());
    if (obj->type_ == PLAYER) {
        players_.push_back(std::unique_ptr<Player>(dynamic_cast<Player*>(obj.release())));
        // When the player is added we need to observe it
        InitPlayerObservers();
    }
    else if (obj->type_ == MONSTER) {
        monsters_.push_back(std::unique_ptr<Monster>(dynamic_cast<Monster*>(obj.release())));
    }
    else if (obj->type_ == PLATFORM || obj->type_ == MOVING_PLATFORM) {
        platforms_.push_back(std::unique_ptr<Platform>(dynamic_cast<Platform*>(obj.release())));
    }
    else {
        otherObjects_.push_back(std::move(obj));
    }
}

// Remove player from the players array
void GameStateManager::RemovePlayer(GameObject* obj) {
    auto it = std::find_if(players_.begin(), players_.end(), [&obj](const std::unique_ptr<Player>& player) {
        return player.get() == obj;
    });
    if (it != players_.end()) {
        players_.erase(it);
    }
}

// Remove monster from the monsters array
void GameStateManager::RemoveMonster(GameObject* obj) {
    auto it = std::find_if(monsters_.begin(), monsters_.end(), [&obj](const std::unique_ptr<Monster>& monster) {
        return monster.get() == obj;
    });
    if (it != monsters_.end()) {
        monsters_.erase(it);
    }
}

// Remove a platform from the platform array
void GameStateManager::RemovePlatform(GameObject* obj) {
    auto it = std::find_if(platforms_.begin(), platforms_.end(), [&obj](const std::unique_ptr<Platform>& platform) {
        return platform.get() == obj;
    });
    if (it != platforms_.end()) {
        platforms_.erase(it);
    }
}

// Remove "Other" objects from the scene
void GameStateManager::RemoveOtherObject(GameObject* obj) {
    auto it = std::find_if(otherObjects_.begin(), otherObjects_.end(), [&obj](const std::unique_ptr<GameObject>& other) {
        return other.get() == obj;
    });
    if (it != otherObjects_.end()) {
        otherObjects_.erase(it);
    }
}

// Remove an object from the GameState
void GameStateManager::RemoveObject(GameObject* obj) {
    // Find and remove the object from the allGameObjects_ vector
    allGameObjects_.erase(std::remove(allGameObjects_.begin(), allGameObjects_.end(), obj), allGameObjects_.end());
    // Call the appropriate function based on the object's type
    switch (obj->type_) {
        case PLAYER:
            RemovePlayer(obj);
            break;
        case MONSTER:
            RemoveMonster(obj);
            break;
        case PLATFORM:
            RemovePlatform(obj);
            break;
        default:
            RemoveOtherObject(obj);
            break;
    }
}

// Return the full GameObject* vector
std::vector<GameObject*> GameStateManager::GetAllObjects() {
    return allGameObjects_;
}

#pragma endregion

#pragma region game state methods

// Init the camera to its base target, offset, rotation, and zoom.
// Currently, supports only one player.
// Call this function just before attempting to render the GameState
// DO NOT CALL UNLESS players_ HAS AT LEAST ONE PLAYER
void GameStateManager::InitCamera() {
    Player* player1 = players_.at(0).get();
    camera_.target = (Vector2){player1->GetPosition().x + 20.0f, player1->GetPosition().y + 20.0f};
    camera_.offset = (Vector2){(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    camera_.rotation = 0.0f;
    camera_.zoom = 1.0f;
}

// Update the camera using the players current position
void GameStateManager::UpdateCamera() {
    Player* player1 = players_.at(0).get();
    camera_.target = (Vector2){ player1->GetPosition().x + 20, player1->GetPosition().y + 20 };
}

// Return the levelOver boolean flag
bool GameStateManager::IsLevelOver() const {
    return levelOver;
}

// Set levelOver to true
void GameStateManager::SetLevelOver() {
    levelOver = true;
}

// Return the camera
Camera2D GameStateManager::GetCamera() {
    return camera_;
}

#pragma endregion

// Retrieve a gameData struct from the GameStateManager, giving the context of the games current state
// Retrieve a gameData struct from the GameStateManager, giving the context of the games current state
gameData GameStateManager::GetGameData() {
    // IMPORTANT: GetPlayerData, and GameStateManager support ONE PLAYER
    gameData data{};
    data.playerPosition = players_[0].get()->GetPosition();
    data.playerData = players_[0].get()->GetPlayerData();
    // Get sizes
    data.numMonsters = monsters_.size();
    data.numPlayers = players_.size();
    data.numPlatforms = platforms_.size();
    data.numOther = otherObjects_.size();
    return data;
}

// Create the InputManager
void GameStateManager::InitInput(EngineSettings* settings) {
    inputManager_ = std::make_unique<InputManager>(players_[0].get(), *settings);
}

// Cleanup the vectors on destruct
GameStateManager::~GameStateManager() {
    players_.clear();
    monsters_.clear();
    platforms_.clear();
    otherObjects_.clear();
}

// Checks if the player hit the monster, and then return if the monster should die
bool GameStateManager::HandlePlayerAttack(Player* player, Monster* monster) {
    Vector2 playerPos = player->GetPosition();
    Vector2 monsterPos = monster->GetPosition();
    // Get attack range and player movement direction
    bool movingRight = player->GetPlayerData()->movingRight_;
    float attackRange = player->GetPlayerData()->attackRange_;
    float playerHeight = player->GetRect().height;

    // Lambda function to simplify the boolean check
    // Is the monster in front of the player and player moving right?
    auto monster_inFront = [=]() {
        // player.x ------ monster.x --- | attackRange // Hit monsters facing right
        bool inRangeX = monsterPos.x > playerPos.x && monsterPos.x <= playerPos.x + attackRange;
        bool inRangeY = (monsterPos.y >= playerPos.y - playerHeight) && (monsterPos.y <= playerPos.y + playerHeight);
        return (inRangeX && inRangeY && movingRight);
    };

    auto monster_behind = [=]() {
        // attackRange | --- monster.x -------- player.x // Hit monsters facing left
        bool inRangeX = monsterPos.x < playerPos.x && monsterPos.x >= playerPos.x - attackRange;
        bool inRangeY = (monsterPos.y >= playerPos.y - playerHeight) && (monsterPos.y <= playerPos.y + playerHeight);
        return (inRangeX && inRangeY && !movingRight);
    };

    // Hit the monster if either condition is true
    if (monster_inFront() || monster_behind()) {
        return monster->HitMonster(player->GetPlayerData()->damage_);
    }
    return false;
}

// Initialize player observers - the player must be initialized before attaching observers
void GameStateManager::InitPlayerObservers() {
    auto playerOne = players_.at(0).get();
    playerOne->AddObserver(this);
    playerOne->AddObserver(SoundManager::GetInstance());
}
