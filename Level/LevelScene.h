//
// Created by ben on 5/16/24.
//

#include <vector>
#include "../Entities/Player.h"
#include "../Renderer/Renderer.h"

#ifndef PLATFORMER_LEVELSCENE_H
#define PLATFORMER_LEVELSCENE_H

class LevelScene {

private:
    std::vector<GameObject*> gameObjects_;

public:
    explicit LevelScene();

    void Update();

    void Draw(Renderer &renderer);

    void AddObject(GameObject* obj);

};


#endif //PLATFORMER_LEVELSCENE_H
