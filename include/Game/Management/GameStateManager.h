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
/*
 * The GameStateManager is responsible for ownership of GameObjects and updating them,
 * as well as any other game state items such as the camera, collisions, or other logic
 */
class GameStateManager {
private:
    bool levelOver;
    void UpdatePlayers();
    void UpdateMonsters();
    // CAMERA/SCENE ONLY SUPPORT ONE PLAYER CURRENTLY, BEWARE
    void UpdateCamera();
    std::vector<std::unique_ptr<Player>> players_;
    std::vector<std::unique_ptr<Monster>> monsters_;
    std::vector<std::unique_ptr<Platform>> platforms_;
    std::vector<std::unique_ptr<GameObject>> otherObjects_;
    std::vector<GameObject*> allGameObjects_;
    Camera2D camera;
public:
    GameStateManager();
    void InitCamera();
    void Update();
    Camera2D GetCamera();
    std::vector<GameObject*> GetAllObjects();
    void SetLevelOver();
    bool IsLevelOver() const;
    void AddObject(std::unique_ptr<GameObject> obj);
    ~GameStateManager();
};

#endif //PLATFORMER_GAMESTATEMANAGER_H
