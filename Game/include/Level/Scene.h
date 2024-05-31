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
    std::vector<std::unique_ptr<Player>> players_;
    std::vector<std::unique_ptr<Monster>> monsters_;
    std::vector<std::unique_ptr<Platform>> platforms_;
    std::vector<std::unique_ptr<GameObject>> otherObjects_;
    Camera2D camera;
public:
    Scene();
    void InitCamera();
    void Update();
    Camera2D GetCamera();
    std::vector<GameObject*> GetAllObjects();
    void SetLevelOver();
    bool IsLevelOver() const;
    void AddObject(std::unique_ptr<GameObject> obj);
    ~Scene();
};

#endif //PLATFORMER_SCENE_H
