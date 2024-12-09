//
// Created by ben on 5/16/24.
//

#include "../../../include/Platform/Renderer.h"
#include "../../../include/Game/Management/InputManager.h"
#include "../../../include/Game/Management/GameStateManager.h"
#include "../../../include/Game/Entities/Effects/ParticleCone.h"
#include <algorithm>
#include <stdexcept>

std::unique_ptr<GameStateManager> GameStateManager::instance = nullptr;

GameStateManager::GameStateManager() {
    levelOver = false;
    mode_ = MODE_GAME;
}

// Window Singleton Pattern
GameStateManager* GameStateManager::GetInstance() {
    //TraceLog(LOG_DEBUG, "GameStateManager::GetInstance() Invoked."); // Log
    if (instance == nullptr) {
        TraceLog(LOG_INFO, "Creating GameStateManager...");
        instance = std::make_unique<GameStateManager>(); // Typical singleton stuff, but I've implemented the instance as a unique ptr
    }
    return instance.get(); // if the window already exists, simply return it
}

#pragma region update gameState methods

// Update all game objects and handle collisions
void GameStateManager::Update() {
    if (mode_ == MODE_GAME) {
        UpdateGame();
    }
    else { // mode_ == MODE_LEVEL
        UpdateLevel();
    }
}

void GameStateManager::UpdateGame() {
    // Update the camera
    UpdateCamera();
    // Update all game objects and handle collisions
    UpdatePlayers(); // update Players
    UpdatePlatforms(); // update Platforms
    // Handle user input
    inputManager_->HandleUserInput();
    UpdateMonsters(); // update Monsters
    UpdateOthers();
    // Transition to edit mode
    if (IsKeyPressed(KEY_L)) {
        mode_ = MODE_EDITOR;
    }
}

void GameStateManager::UpdateLevel() {
    inputManager_->HandleEditorInput(camera_);
}

void GameStateManager::UpdatePlatforms() {
    #pragma omp parallel for
    for (const auto& platform : platforms_) {
        platform->Update();
    }
}

TileManager& GameStateManager::GetTileManager() const {
    if (!tileManager_) {
        TraceLog(LOG_FATAL, "TileManager is not initialized!");
        throw std::runtime_error("TileManager is null");
    }
    return *tileManager_;
}

void GameStateManager::SetTileManager(std::unique_ptr<TileManager> tileManager) {
    // Transfer ownership of TileManager
    tileManager_ = std::move(tileManager);

    // Get the tiles and move them into the game objects
    auto tiles = tileManager_->GetTiles();
    for (auto& row : tiles) {
        for (auto& tile : row) {
            if (tile)
                AddObject(std::move(tile)); // Move tile ownership
        }
    }
}



// Update all players in the scene by iterating over the players, calling update, and then checking for collisions
void GameStateManager::UpdatePlayers() {
    for (auto& player : players_) {
        player->Update();
        HandleCollisions(player.get());
    }
}

// Handle player and monster attacks onscreen
void GameStateManager::UpdateAttacks(Player* player) {
    PlayerAttackEffect(player);
    // Iterate over all monsters
    #pragma omp parallel for
    for (auto& monster : monsters_) {
        HandlePlayerAttack(player, monster.get());
    }
}

// Update all players in the scene by iterating over the monsters, calling update, and then checking for collisions
void GameStateManager::UpdateMonsters() {
    // Create an array to defer monster removals
    std::vector<GameObject*> toRemove;
    #pragma omp parallel for
    for (auto& monster : monsters_) {
        monster->Update();
        for (auto& player : players_) {
            monster->CollideWithPlayer(player.get());
        }
        // Handle collisions with platforms and tiles
        HandleCollisions(monster.get());
        // Check if we need to remove the monster from the GameState
        if (monster->ShouldRemove()) {
            toRemove.push_back(monster.get());
        }
    }
    // Remove monsters
    for (const auto& monster : toRemove) {
        RemoveObject(monster);
    }
}

void GameStateManager::HandleCollisions(GameObject* obj) const {
    for (auto& platform : platforms_) {
        CollisionHandler::HandlePlatformCollision(obj, platform.get());
    }
#pragma omp parallel for // update the other objects in parallel using threads
    for (const auto& row : tiles_) {
        for (const auto& tile : row) {
            CollisionHandler::HandlePlatformCollision(obj, tile.get()); // Trees are also otherObjects, and I don't want to collide with them
        }
    }
}

void GameStateManager::UpdateOthers() {
    for (auto it = otherObjects_.begin(); it != otherObjects_.end(); ) {
        (*it)->Update();
        if ((*it)->ShouldRemove()) {
            RemoveObject(it->get());
        } else {
            ++it;
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
    if (obj->type_ == PLAYER) {
        InitObservers(dynamic_cast<Subject*>(obj.get())); // PLAYER is a subject, init observers
        players_.push_back(std::unique_ptr<Player>(dynamic_cast<Player*>(obj.release())));
        allGameObjects_.push_back(players_.back().get()); // Insert at the end
    }
    else if (obj->type_ == MONSTER) {
        InitObservers(dynamic_cast<Subject*>(obj.get())); // MONSTER is a subject, init observers
        monsters_.push_back(std::unique_ptr<Monster>(dynamic_cast<Monster*>(obj.release())));
        allGameObjects_.insert(allGameObjects_.begin(), monsters_.back().get()); // Insert at the beginning
    }
    else if (obj->type_ == PLATFORM || obj->type_ == MOVING_PLATFORM) {
        platforms_.push_back(std::unique_ptr<Platform>(dynamic_cast<Platform*>(obj.release())));
        allGameObjects_.insert(allGameObjects_.begin() + (long)monsters_.size(), platforms_.back().get()); // Insert after monsters
    }
    else if (obj->type_ == TILE) {
        auto tile = std::unique_ptr<Tile>(dynamic_cast<Tile*>(obj.release()));
        if (!tiles_.empty()) {
            tiles_.back().push_back(std::move(tile));
        } else {
            tiles_.emplace_back();
            tiles_.back().push_back(std::move(tile));
        }
        allGameObjects_.insert(allGameObjects_.begin() + (long)monsters_.size() + (long)platforms_.size() + tiles_.back().size() - 1, tiles_.back().back().get());
    }
    else {
        otherObjects_.push_back(std::move(obj));
        allGameObjects_.insert(allGameObjects_.begin() + (long)monsters_.size() + (long)platforms_.size() + tiles_.size(), otherObjects_.back().get());
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
// Remove monster from the monsters array
void GameStateManager::RemoveMonster(GameObject* obj) {
    auto it = std::find_if(monsters_.begin(), monsters_.end(), [&obj](const std::unique_ptr<Monster>& monster) {
        return monster.get() == obj;
    });
    if (it != monsters_.end()) {
        // Remove from monsters_
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
    camera_.offset = (Vector2){static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f};
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
Camera2D GameStateManager::GetCamera() const {
    return camera_;
}

#pragma endregion

// Retrieve a gameData struct from the GameStateManager, giving the context of the games current state
// Retrieve a gameData struct from the GameStateManager, giving the context of the games current state
gameData GameStateManager::GetGameData() const {
    // IMPORTANT: GetPlayerData, and GameStateManager support ONE PLAYER
    gameData data{};
    data.player = players_.at(0).get();
    // Get sizes
    data.numMonsters = monsters_.size();
    data.numPlayers = players_.size();
    data.numPlatforms = platforms_.size();
    data.numOther = otherObjects_.size();
    return data;
}

// Get all players
std::vector<Player*> GameStateManager::GetPlayers() const {
    std::vector<Player*> players;
    players.reserve(players_.size());
    for (auto& player : players_) {
        players.push_back(player.get());
    }
    return players;
}

InputManager *GameStateManager::GetInputManager() const {
    return inputManager_.get();
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
void GameStateManager::HandlePlayerAttack(Player* player, Monster* monster) {
    Vector2 playerPos = player->GetPosition();
    Vector2 monsterPos = monster->GetPosition();
    // Get attack range and player movement direction
    bool movingRight = player->GetMovingRight();
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
        monster->HitMonster(player->GetPlayerData()->damage_);
    }
}

// Initialize the observers on a subject
// Should be called whenever a subject is added to the GameState that game systems need to observe
void GameStateManager::InitObservers(Subject* subject) {
    subject->AddObserver(this);
    subject->AddObserver(SoundManager::GetInstance());
}

void GameStateManager::PlayerAttackEffect(Player* player) {
    // Attack effect
    auto effect = std::make_unique<ParticleCone>(player->GetPosition(),
    Vector2{player->GetRect().width, player->GetRect().height}, player->GetMovingRight(), 1000);
    AddObject(std::move(effect));
}

void GameStateManager::SetMode(const Mode mode) {
    mode_ = mode;
}

Mode GameStateManager::GetMode() const {
    return mode_;
}


