//
// Created by ben on 5/16/24.
//

#pragma once

#ifndef PLATFORMER_SCENE_H
#define PLATFORMER_SCENE_H

#include <vector>
#include "../Entities/Player/Player.h"
#include "../Entities/Monsters/Monster.h"
#include "../Entities/Objects/Platform.h"

class Scene {

private:
    bool levelOver;
    void UpdatePlayers();
    void UpdateMonsters();
    // CAMERA/SCENE ONLY SUPPORT ONE PLAYER CURRENTLY, BEWARE
    void UpdateCamera();
    std::vector<Player*> players_;
    std::vector<Monster*> monsters_;
    std::vector<Platform*> platforms_;
    std::vector<GameObject*> otherObjects_;
    Camera2D camera;
public:
    Scene();
    void InitCamera();
    void Update();
    Camera2D GetCamera();
    std::vector<GameObject*> GetAllObjects();
    void SetLevelOver();
    bool IsLevelOver();
    void AddObject(GameObject* obj);
    ~Scene();
};

#endif //PLATFORMER_SCENE_H
