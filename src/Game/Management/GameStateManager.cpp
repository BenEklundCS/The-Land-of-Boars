//
// Created by ben on 5/16/24.
//

#include "../../../include/Platform/Renderer.h"
#include "../../../include/Game/Management/InputManager.h"
#include "../../../include/Game/Management/GameStateManager.h"
#include "../../../include/Game/Entities/Effects/ParticleCone.h"
#include <algorithm>
#include <stdexcept>

// Initialize the static singleton instance
std::unique_ptr<GameStateManager> GameStateManager::instance = nullptr;

/**
 * @brief Constructor for the GameStateManager.
 *
 * Initializes the default game state, starting in `MODE_GAME`.
 */
GameStateManager::GameStateManager() {
    levelOver = false;
    mode_ = MODE_GAME;
}

/**
 * @brief Retrieves the singleton instance of the GameStateManager.
 *
 * If the instance does not already exist, it is created. This ensures that only
 * one GameStateManager exists during the application's lifetime.
 *
 * @return GameStateManager* Pointer to the singleton instance.
 */
GameStateManager* GameStateManager::GetInstance() {
    //TraceLog(LOG_DEBUG, "GameStateManager::GetInstance() Invoked."); // Log
    if (instance == nullptr) {
        TraceLog(LOG_INFO, "Creating GameStateManager...");
        instance = std::make_unique<GameStateManager>(); // Typical singleton stuff, but I've implemented the instance as a unique ptr
    }
    return instance.get(); // if the window already exists, simply return it
}

#pragma region update gameState methods

/**
 * @brief Main update loop for the game state.
 *
 * Delegates updates to either `UpdateGame` or `UpdateLevel` based on the current mode.
 */
void GameStateManager::Update() {
    if (mode_ == MODE_GAME) {
        UpdateGame();
    }
    else { // mode_ == MODE_LEVEL
        UpdateLevel();
    }
}

/**
 * @brief Updates game-related logic (e.g., players, monsters, platforms).
 */
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

/**
 * @brief Handles updates in editor mode (e.g., camera navigation, tile editing).
 */
void GameStateManager::UpdateLevel() {
    inputManager_->HandleEditorInput(camera_);
}

/**
 * @brief Updates all platforms in the game using parallel processing.
 */
void GameStateManager::UpdatePlatforms() {
    #pragma omp parallel for
    for (const auto& platform : platforms_) {
        platform->Update();
    }
}

/**
 * @brief Retrieves the tile manager.
 *
 * @throws std::runtime_error If the tile manager is not initialized.
 * @return TileManager& Reference to the tile manager.
 */
TileManager& GameStateManager::GetTileManager() const {
    if (!tileManager_) {
        TraceLog(LOG_FATAL, "TileManager is not initialized!");
        throw std::runtime_error("TileManager is null");
    }
    return *tileManager_;
}

/**
 * @brief Sets the tile manager and reloads tiles.
 *
 * @param tileManager Unique pointer to the new tile manager.
 */
void GameStateManager::SetTileManager(std::unique_ptr<TileManager> tileManager) {
    // Transfer ownership of TileManager
    tileManager_ = std::move(tileManager);
    ReloadTiles();
}

/**
 * @brief Reloads tiles into the game state, populating `tiles_`
 */
void GameStateManager::ReloadTiles() {
    const auto& tiles = tileManager_->GetTiles();

    // Clear the tiles_ and reserve memory for rows
    tiles_.clear();
    tiles_.reserve(tiles.size());

    // Populate tiles_
    for (const auto& row : tiles) {
        std::vector<Tile*> tileRow; // A row of raw pointers to tiles
        tileRow.reserve(row.size());

        for (const auto& tile : row) {
            if (tile) {
                tileRow.push_back(tile.get());        // Add raw pointer to tiles_
            }
        }
        tiles_.push_back(std::move(tileRow));
    }
}

/**
 * @brief Updates all players and handles collisions.
 */
void GameStateManager::UpdatePlayers() {
    for (auto& player : players_) {
        player->Update();
        HandleCollisions(player.get());
    }
}

/**
 * @brief Updates player attacks, running animations and iterating over the array of monsters.
 */
void GameStateManager::UpdateAttacks(Player* player) {
    PlayerAttackEffect(player);
    // Iterate over all monsters
    #pragma omp parallel for
    for (auto& monster : monsters_) {
        HandlePlayerAttack(player, monster.get());
    }
}

/**
 * @brief Updates all monsters and handles their collisions and removal.
 */
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

/**
 * @brief Handles collisions for a given game object.
 *
 * @param obj Pointer to the game object for collision handling.
 */
void GameStateManager::HandleCollisions(GameObject* obj) const {
    for (auto& platform : platforms_) {
        CollisionHandler::HandlePlatformCollision(obj, platform.get());
    }
    #pragma omp parallel for // update the other objects in parallel using threads
    for (const auto& row : tiles_) {
        for (const auto& tile : row) {
            CollisionHandler::HandlePlatformCollision(obj, tile); // Trees are also otherObjects, and I don't want to collide with them
        }
    }
}

/**
 * @brief Updates other non-player, non-monster objects in the game.
 */
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

/**
 * @brief Notifies the GameStateManager of an event.
 *
 * Handles game events triggered by game objects using the observer pattern.
 *
 * @param entity Pointer to the game object triggering the event.
 * @param event The event being triggered.
 */
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

/**
 * @brief Adds a game object to the GameStateManager.
 *
 * The GameStateManager takes unique ownership of the object. The object
 * must not be null, as undefined behavior will occur.
 *
 * @param obj Unique pointer to the game object being added.
 */
void GameStateManager::AddObject(std::unique_ptr<GameObject> obj) {
    if (obj->type_ == PLAYER) {
        InitObservers(dynamic_cast<Subject*>(obj.get())); // PLAYER is a subject, init observers
        players_.push_back(std::unique_ptr<Player>(dynamic_cast<Player*>(obj.release())));
    }
    else if (obj->type_ == MONSTER) {
        InitObservers(dynamic_cast<Subject*>(obj.get())); // MONSTER is a subject, init observers
        monsters_.push_back(std::unique_ptr<Monster>(dynamic_cast<Monster*>(obj.release())));
    }
    else if (obj->type_ == PLATFORM || obj->type_ == MOVING_PLATFORM) {
        platforms_.push_back(std::unique_ptr<Platform>(dynamic_cast<Platform*>(obj.release())));
    }
    else {
        otherObjects_.push_back(std::move(obj));
    }
}


/**
 * @brief Removes a player object from the `players_` vector.
 *
 * Searches for the specified player and removes it from the scene if found.
 *
 * @param obj Pointer to the player object to remove.
 */
void GameStateManager::RemovePlayer(GameObject* obj) {
    auto it = std::find_if(players_.begin(), players_.end(), [&obj](const std::unique_ptr<Player>& player) {
        return player.get() == obj;
    });
    if (it != players_.end()) {
        players_.erase(it);
    }
}

/**
 * @brief Removes a monster object from the `monsters_` vector.
 *
 * Searches for the specified monster and removes it from the scene if found.
 *
 * @param obj Pointer to the monster object to remove.
 */
void GameStateManager::RemoveMonster(GameObject* obj) {
    auto it = std::find_if(monsters_.begin(), monsters_.end(), [&obj](const std::unique_ptr<Monster>& monster) {
        return monster.get() == obj;
    });
    if (it != monsters_.end()) {
        // Remove from monsters_
        monsters_.erase(it);
    }
}

/**
 * @brief Removes a platform object from the `platforms_` vector.
 *
 * Searches for the specified platform and removes it from the scene if found.
 *
 * @param obj Pointer to the platform object to remove.
 */
void GameStateManager::RemovePlatform(GameObject* obj) {
    auto it = std::find_if(platforms_.begin(), platforms_.end(), [&obj](const std::unique_ptr<Platform>& platform) {
        return platform.get() == obj;
    });
    if (it != platforms_.end()) {
        platforms_.erase(it);
    }
}

/**
 * @brief Removes an object from the `otherObjects_` vector.
 *
 * Searches for the specified object and removes it from the scene if found.
 *
 * @param obj Pointer to the object to remove.
 */
void GameStateManager::RemoveOtherObject(GameObject* obj) {
    auto it = std::find_if(otherObjects_.begin(), otherObjects_.end(), [&obj](const std::unique_ptr<GameObject>& other) {
        return other.get() == obj;
    });
    if (it != otherObjects_.end()) {
        otherObjects_.erase(it);
    }
}

/**
 * @brief Removes a game object from the GameState based on its type.
 *
 * Delegates removal to the appropriate type-specific method (`RemovePlayer`, `RemoveMonster`, etc.).
 *
 * @param obj Pointer to the game object to remove.
 */
void GameStateManager::RemoveObject(GameObject* obj) {
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

/**
 * @brief Retrieves all game objects in the GameStateManager.
 *
 * Combines all players, monsters, platforms, tiles, and other objects into a single vector
 * for easy access or processing.
 *
 * @return std::vector<GameObject*> A vector containing pointers to all game objects.
 */
std::vector<GameObject*> GameStateManager::GetAllObjects() {
    std::vector<GameObject*> allObjects;

    // Reserve space for efficiency
    allObjects.reserve(players_.size() + monsters_.size() + platforms_.size() + otherObjects_.size() + tiles_.size() * tiles_[0].size());

    // Add monsters
    for (const auto& monster : monsters_) {
        allObjects.push_back(monster.get());
    }

    // Add platforms
    for (const auto& platform : platforms_) {
        allObjects.push_back(platform.get());
    }

    // Add other objects
    for (const auto& obj : otherObjects_) {
        allObjects.push_back(obj.get());
    }

    // Add tiles
    for (const auto& row : tiles_) {
        for (const auto& tile : row) {
            if (tile) {
                allObjects.push_back(tile);
            }
        }
    }

    // Add players
    for (const auto& player : players_) {
        allObjects.push_back(player.get());
    }

    return allObjects;
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

/**
 * @brief Checks whether the level is over.
 *
 * @return bool True if the level is over, false otherwise.
 */
bool GameStateManager::IsLevelOver() const {
    return levelOver;
}

/**
 * @brief Sets the levelOver flag to true, marking the level as completed.
 */
void GameStateManager::SetLevelOver() {
    levelOver = true;
}

/**
 * @brief Retrieves the camera object.
 *
 * Provides access to the current camera state for rendering and input handling.
 *
 * @return Camera2D The camera object used by the game.
 */
Camera2D GameStateManager::GetCamera() const {
    return camera_;
}

#pragma endregion

/**
 * @brief Retrieves a structured representation of the current game state.
 *
 * Provides an overview of the game's state, including the number of players,
 * monsters, platforms, and other objects, as well as the player's data.
 *
 * @return gameData A struct containing details about the current game state.
 */
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

/**
 * @brief Retrieves all players in the game.
 *
 * Extracts raw pointers to player objects from the `players_` vector.
 *
 * @return std::vector<Player*> A vector of pointers to all players.
 */
std::vector<Player*> GameStateManager::GetPlayers() const {
    std::vector<Player*> players;
    players.reserve(players_.size());
    for (auto& player : players_) {
        players.push_back(player.get());
    }
    return players;
}

/**
 * @brief Retrieves the input manager for the game.
 *
 * Provides access to the `InputManager` instance controlling user input.
 *
 * @return InputManager* Pointer to the game's input manager.
 */
InputManager *GameStateManager::GetInputManager() const {
    return inputManager_.get();
}


/**
 * @brief Initializes the input manager for the game.
 *
 * Links the `InputManager` to the first player in the `players_` vector
 * and applies the given engine settings.
 *
 * @param settings Pointer to the engine settings for input configuration.
 */
void GameStateManager::InitInput(EngineSettings* settings) {
    inputManager_ = std::make_unique<InputManager>(players_[0].get(), *settings);
}

/**
 * @brief Destructor for the GameStateManager.
 *
 * Cleans up all dynamically allocated resources, including players, monsters,
 * platforms, and other objects.
 */
GameStateManager::~GameStateManager() {
    players_.clear();
    monsters_.clear();
    platforms_.clear();
    otherObjects_.clear();
}

/**
 * @brief Handles player attacks, calculating whether a monster is hit based on proximity and player direction.
 *
 * Checks for collisions between the player and monsters within the attack range.
 * If a monster is hit, it takes damage from the player's attack.
 *
 * @param player Pointer to the player performing the attack.
 * @param monster Pointer to the monster being checked for a hit.
 */
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

/**
 * @brief Initializes observers on a subject.
 *
 * Adds the `GameStateManager` and `SoundManager` as observers to the given subject.
 *
 * @param subject Pointer to the subject object to observe.
 */
void GameStateManager::InitObservers(Subject* subject) {
    subject->AddObserver(this);
    subject->AddObserver(SoundManager::GetInstance());
}

/**
 * @brief Creates a particle cone effect for a player's attack.
 *
 * Spawns a particle effect at the player's position, with parameters based on
 * the player's size and direction.
 *
 * @param player Pointer to the player initiating the attack effect.
 */
void GameStateManager::PlayerAttackEffect(Player* player) {
    // Attack effect
    auto effect = std::make_unique<ParticleCone>(player->GetPosition(),
    Vector2{player->GetRect().width, player->GetRect().height}, player->GetMovingRight(), 1000);
    AddObject(std::move(effect));
}

/**
 * @brief Sets the current game mode.
 *
 * Updates the game state to either `MODE_GAME`, `MODE_EDITOR`, or another mode.
 *
 * @param mode The new game mode to set.
 */
void GameStateManager::SetMode(const Mode mode) {
    mode_ = mode;
}

/**
 * @brief Retrieves the current game mode.
 *
 * @return Mode The current mode of the game (`MODE_GAME`, `MODE_EDITOR`, etc.).
 */
Mode GameStateManager::GetMode() const {
    return mode_;
}




