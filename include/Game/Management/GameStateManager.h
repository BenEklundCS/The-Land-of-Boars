//
// Created by ben on 5/16/24.
//

#pragma once

#ifndef PLATFORMER_GAMESTATEMANAGER_H
#define PLATFORMER_GAMESTATEMANAGER_H

#include <vector>
#include "../Entities/Player/Player.h"
#include "../Entities/Monsters/Monster.h"
#include "../Entities/Objects/Platform.h"
#include "TileManager.h"
#include "SoundManager.h"
#include "../Entities/CollisionHandler.h"

/**
 * @file GameStateManager.h
 * @brief Manages the overall state of the game, including ownership, updates, and interactions of all game objects.
 *
 * The `GameStateManager` handles the game loop, updates game objects, manages camera movement, and processes input.
 * It serves as the central hub for managing the game state, ensuring smooth integration between various systems.
 */

class InputManager;
struct EngineSettings;

/**
 * @struct gameData
 * @brief Aggregates high-level game statistics and references for debugging or rendering.
 */
struct gameData {
    Player* player; ///< Pointer to the primary player object.
    size_t numPlayers; ///< Number of players in the game (currently supports only one).
    size_t numMonsters; ///< Number of monsters in the game.
    size_t numPlatforms; ///< Number of platforms in the game.
    size_t numOther; ///< Number of other game objects.
};

/**
 * @enum Mode
 * @brief Represents the current mode of the game.
 */
enum Mode {
    MODE_GAME, ///< Standard gameplay mode.
    MODE_EDITOR ///< Level editor mode.
};

/**
 * @enum LevelResult
 * @brief Why a level ended.
 *
 * "Level over" alone is not enough - the Engine advances to the next level on a
 * win but replays the current one on a death.
 */
enum LevelResult {
    LEVEL_RUNNING,   ///< Still being played.
    LEVEL_COMPLETED, ///< Player reached the goal.
    LEVEL_FAILED     ///< Player died.
};

/**
 * @class GameStateManager
 * @brief Manages the state of the game, including updates to game objects, camera, and other game logic.
 *
 * The `GameStateManager` owns and manages all game objects (players, monsters, platforms, etc.), processes collisions,
 * handles camera movement, and integrates input management. It also serves as an observer for events triggered by game objects.
 *
 * **Note:** Multiplayer is not currently supported.
 */
class GameStateManager : public Observer {
private:
    static std::unique_ptr<GameStateManager> instance; ///< Singleton instance.
    bool levelOver; ///< Flag indicating whether the level is over.
    /// Why the level ended - the Engine advances on a win but retries on a death.
    LevelResult levelResult_ = LEVEL_RUNNING;
    Rectangle goal_{}; ///< World-space region that completes the level when touched. Zero-size = no goal.

    // Update methods
    void UpdateGame(); ///< Updates the entire game state.
    void CheckLevelEndConditions(); ///< Decides whether the level was won or lost this frame.
    void UpdateLevel(); ///< Updates the current level.
    void UpdatePlayers(); ///< Updates all player objects.
    void UpdateMonsters(); ///< Updates all monster objects.
    void HandleCollisions(GameObject* obj); ///< Handles collisions for a given game object.
    void UpdatePlatforms(); ///< Updates all platform objects.
    void UpdateOthers(); ///< Updates all other game objects.

    // Effects
    void PlayerAttackEffect(Player* player); ///< Handles attack effects for the player.


    // Object deleters
    void RemoveObject(GameObject* obj); // NEW: Add RemoveObject here
    void RemovePlayer(GameObject* obj); ///< Removes a player object.
    void RemoveMonster(GameObject* obj); ///< Removes a monster object.
    void RemovePlatform(GameObject* obj); ///< Removes a platform object.
    void RemoveOtherObject(GameObject* obj); ///< Removes any other object.

    // Observer initialization
    void InitObservers(Subject* subject);

    // Camera updates
    void UpdateCamera(); ///< Updates the camera to follow the player.

    // Attack handling
    static void HandlePlayerAttack(Player* player, Monster* monster); ///< Handles player attacks on monsters.
    void UpdateAttacks(Player* player); ///< Updates attack-related logic for a player.

    // Game object storage
    std::vector<std::unique_ptr<Player>> players_; ///< Vector of player objects.
    std::vector<std::unique_ptr<Monster>> monsters_; ///< Vector of monster objects.
    std::vector<std::unique_ptr<Platform>> platforms_; ///< Vector of platform objects.
    std::vector<std::unique_ptr<GameObject>> otherObjects_; ///< Vector of miscellaneous game objects.
    std::vector<std::vector<Tile*>> tiles_; ///< Vector of tiles, managed by the TileManager.

    // Helper function for player coin interactions
    void PlayerPickUpCoins(GameObject *obj);

    // Camera
    Camera2D camera_{}; ///< Game camera.

    // Game systems
    std::unique_ptr<InputManager> inputManager_; ///< Input manager for processing user input.
    std::unique_ptr<SoundManager> soundManager_; ///< Sound manager for playing sounds.
    std::unique_ptr<TileManager> tileManager_; ///< Tile manager for handling tiles.

    // Current game mode
    Mode mode_;

public:
    /**
     * @brief Constructs a new GameStateManager instance.
     */
    GameStateManager();

    /**
     * @brief Gets the singleton instance of the GameStateManager.
     * @return Pointer to the GameStateManager instance.
     */
    static GameStateManager* GetInstance();

    /**
     * @brief Initializes the camera for the game.
     */
    void InitCamera();

    /**
     * @brief Updates the game state, including all game objects and camera.
     */
    void Update();

    /**
     * @brief Gets the current game camera.
     * @return The Camera2D object.
     */
    [[nodiscard]] Camera2D GetCamera() const;

    /**
     * @brief Retrieves all game objects in the current state.
     * @return A vector of pointers to all game objects.
     */
    std::vector<GameObject*> GetAllObjects();

    /**
     * @brief Marks the level as over.
     */
    void SetLevelOver();

    /**
     * @brief Checks if the level is over.
     * @return True if the level is over, false otherwise.
     */
    [[nodiscard]] bool IsLevelOver() const;

    /**
     * @brief Destroys the singleton so the next GetInstance() builds a fresh state.
     *
     * Required for multi-level play: the manager owns every entity, the tile
     * manager and the camera, so without this the second level would be built
     * on top of the first one's objects.
     */
    static void Reset();

    /**
     * @brief Marks the level finished, recording why.
     */
    void SetLevelResult(LevelResult result);

    /**
     * @brief Why the level ended (LEVEL_RUNNING while still in play).
     */
    [[nodiscard]] LevelResult GetLevelResult() const { return levelResult_; }

    /**
     * @brief Sets the world-space region that completes the level when touched.
     */
    void SetGoal(Rectangle goal) { goal_ = goal; }

    /**
     * @brief The level's goal region. Zero width/height means the level has no goal.
     */
    [[nodiscard]] Rectangle GetGoal() const { return goal_; }

    /**
     * @brief Retrieves aggregated game data for debugging or rendering.
     * @return A `gameData` structure containing game statistics.
     */
    [[nodiscard]] gameData GetGameData() const;

    /**
     * @brief Gets all players in the game.
     * @return A vector of pointers to Player objects.
     */
    [[nodiscard]] std::vector<Player*> GetPlayers() const;

    /**
     * @brief Adds a new game object to the scene.
     * @param obj A unique pointer to the game object.
     */
    void AddObject(std::unique_ptr<GameObject> obj);

    /**
     * @brief Initializes input management for the game.
     * @param settings Pointer to engine settings for configuring input.
     */
    void InitInput(EngineSettings* settings);

    /**
     * @brief Reacts to events as an observer.
     * @param entity The entity triggering the event.
     * @param event The event type.
     */
    void OnNotify(const GameObject* entity, Events event) override;

    // Tile management
    [[nodiscard]] TileManager& GetTileManager() const; ///< Retrieves the TileManager instance.
    void SetTileManager(std::unique_ptr<TileManager> tileManager); ///< Sets a new TileManager.
    void ReloadTiles(); ///< Reloads tiles from the TileManager.

    // Input management
    InputManager* GetInputManager() const; ///< Retrieves the InputManager instance.

    // Game mode management
    [[nodiscard]] Mode GetMode() const; ///< Gets the current game mode.
    void SetMode(Mode mode); ///< Sets the current game mode.

    /**
     * @brief Destroys the GameStateManager instance.
     */
    ~GameStateManager() override;

    void DropCoins();

    void DropCoins(Vector2 monsterPosition);
};

#endif //PLATFORMER_GAMESTATEMANAGER_H
