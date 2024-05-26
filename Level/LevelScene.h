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
    std::vector<GameObject*> gameObjects_;
public:
    LevelScene();
    void Update();
    void Draw(Renderer &renderer);
    void AddObject(GameObject* obj);
    ~LevelScene();
};


#endif //PLATFORMER_LEVELSCENE_H
