//
// Created by ben on 5/16/24.
//

#pragma once

#ifndef PLATFORMER_LEVELSCENE_H
#define PLATFORMER_LEVELSCENE_H

#include <vector>
#include "../Entities/Player/Player.h"
#include "../Renderer/Renderer.h"
#include "../Entities/Monsters/Monster.h"
#include "../Entities/Objects/Platform.h"

class LevelScene {

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
    LevelScene();
    void StartScene();
    static void SetLevelOver();
    void AddObject(GameObject* obj);
    ~LevelScene();
};


#endif //PLATFORMER_LEVELSCENE_H
