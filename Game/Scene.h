//
// Created by ben on 5/16/24.
//

#pragma once

#ifndef PLATFORMER_SCENE_H
#define PLATFORMER_SCENE_H

#include <vector>
#include "../Entities/Player/Player.h"
#include "../Renderer/Renderer.h"
#include "../Entities/Monsters/Monster.h"
#include "../Entities/Objects/Platform.h"

class Scene {

private:
    static bool levelOver;
    void Update();
    void Draw();
    static bool IsLevelOver();
    std::vector<Player*> players_;
    std::vector<Monster*> monsters_;
    std::vector<Platform*> platforms_;
    std::vector<GameObject*> otherObjects_;
public:
    Scene();
    void StartScene();
    static void SetLevelOver();
    void AddObject(GameObject* obj);
    ~Scene();
};


#endif //PLATFORMER_SCENE_H
