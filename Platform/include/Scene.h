//
// Created by ben on 5/16/24.
//

#pragma once

#ifndef PLATFORMER_SCENE_H
#define PLATFORMER_SCENE_H

#include <vector>
#include "Renderer.h"
#include "../../Game/src/Entities/Player/Player.h"
#include "../../Game/include/Monster.h"
#include "../../Game/include/Platform.h"

class Scene {

private:
    Renderer renderer;
    static bool levelOver;
    void Update();
    void Draw();
    static bool IsLevelOver();
    std::vector<Player*> players_;
    std::vector<Monster*> monsters_;
    std::vector<Platform*> platforms_;
    std::vector<GameObject*> otherObjects_;
    void UpdatePlayers();
    void UpdateMonsters();
    // CAMERA/SCENE ONLY SUPPORT ONE PLAYER CURRENTLY, BEWARE
    Camera2D camera;
    void UpdateCamera();
    void InitCamera();
public:
    Scene();
    void StartScene();
    static void SetLevelOver();
    void AddObject(GameObject* obj);
    ~Scene();
};

#endif //PLATFORMER_SCENE_H
