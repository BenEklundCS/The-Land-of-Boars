//
// Created by ben on 5/16/24.
//

#ifndef PLATFORMER_LEVELSCENE_H
#define PLATFORMER_LEVELSCENE_H

#include <vector>
#include "../Entities/Player.h"
#include "../Renderer/Renderer.h"

class LevelScene {

private:
    std::vector<GameObject*> gameObjects_;
    Player* player_;
public:
    explicit LevelScene(Player *player);
    void Update();
    void Draw(Renderer &renderer);
    void AddObject(GameObject* obj);
    void HandlePlayerCollisions();
};


#endif //PLATFORMER_LEVELSCENE_H
