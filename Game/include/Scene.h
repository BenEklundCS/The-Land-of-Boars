//
// Created by ben on 5/16/24.
//

#pragma once

#ifndef PLATFORMER_SCENE_H
#define PLATFORMER_SCENE_H

#include <vector>
#include "../src/Entities/Player/Player.h"
#include "Monster.h"
#include "Platform.h"

class Scene {

private:
    static bool levelOver;
    void UpdatePlayers();
    void UpdateMonsters();
    // CAMERA/SCENE ONLY SUPPORT ONE PLAYER CURRENTLY, BEWARE
    Camera2D camera;
public:
    Scene();
    void UpdateCamera();
    void InitCamera();
    void Update();
    Camera2D GetCamera();
    std::vector<Player*> players_;
    std::vector<Monster*> monsters_;
    std::vector<Platform*> platforms_;
    std::vector<GameObject*> otherObjects_;
    static void SetLevelOver();
    static bool IsLevelOver();
    void AddObject(GameObject* obj);
    ~Scene();
};

#endif //PLATFORMER_SCENE_H
