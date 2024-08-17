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
#include "../../Platform/Engine.h"
#include "SoundManager.h"

class InputManager;
struct EngineSettings;

struct gameData {
    Vector2 playerPosition;
    const playerDataStruct* playerData;
    size_t numPlayers;
    size_t numMonsters;
    size_t numPlatforms;
    size_t numOther;
};

/*
 * The GameStateManager is responsible for ownership of GameObjects and updating them,
 * as well as any other game state items such as the camera, collisions, or other logic
 */
// IMPORTANT, GameStateManager uses a Vector to store players_, but currently only supports ONE player.
// Multiplayer support is not planned for this project.
class GameStateManager : public Observer {
private:
    static std::unique_ptr<GameStateManager> instance;
    bool levelOver; // Flag for if the level is over
    void UpdatePlayers(); // Update the player vector
    void UpdateMonsters(); // Update the monster vector
    void UpdatePlatforms();
    // Deleters of objects
    void InitPlayerObservers();
    void RemovePlayer(GameObject *obj);
    void RemoveMonster(GameObject *obj);
    void RemovePlatform(GameObject *obj);
    void RemoveObject(GameObject *obj);
    void RemoveOtherObject(GameObject *obj);
    // CAMERA/SCENE ONLY SUPPORT ONE PLAYER CURRENTLY, BEWARE
    void UpdateCamera(); // Update the camera
    static bool HandlePlayerAttack(Player* player, Monster* monster); // Handle the players attack on the game state, hitting everything within distance
    std::vector<std::unique_ptr<Player>> players_; // player object vector
    std::vector<std::unique_ptr<Monster>> monsters_; // monster object vector
    std::vector<std::unique_ptr<Platform>> platforms_; // platform object vector
    std::vector<std::unique_ptr<GameObject>> otherObjects_; // other object vector
    std::vector<GameObject*> allGameObjects_; // All game object vector
    Camera2D camera_{}; // Camera
    std::unique_ptr<InputManager> inputManager_;
    std::unique_ptr<SoundManager> soundManager_;
public:
    GameStateManager(); // Constructor
    static GameStateManager* GetInstance();
    void InitCamera(); // Initialize the camera - call before rendering
    void Update(); // Update the game state
    // Call to update attacks, must pass a player
    void UpdateAttacks(Player* player);
    Camera2D GetCamera(); // Get the Camera2D
    std::vector<GameObject*> GetAllObjects(); // Get all game objects from the GameState
    void SetLevelOver(); // Set levelOver to true
    [[nodiscard]] bool IsLevelOver() const; // Return the levelOver flag
    gameData GetGameData();
    void AddObject(std::unique_ptr<GameObject> obj); // Add a GameObject to the scene
    void InitInput(EngineSettings* settings); // call to make input available to the GameState
    void OnNotify(const GameObject* entity, Events event) override;
    ~GameStateManager() override; // Destructor
    void PlayerAttackEffect();

    void UpdateOthers();
};

#endif //PLATFORMER_GAMESTATEMANAGER_H
