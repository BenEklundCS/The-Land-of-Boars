//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Window.h"
#include "../Entities/GameObject.h"
#include "../Entities/Monsters/Monster.h"
#include "../Entities/Objects/Platform.h"

#ifndef PLATFORMER_RENDERER_H
#define PLATFORMER_RENDERER_H

class Renderer {
private:
    static void RenderBackground();
    std::vector<Player*> players_;
    std::vector<Monster*> monsters_;
    std::vector<Platform*> platforms_;
    std::vector<GameObject*> otherObjects_;
public:
    Renderer();
    Renderer(std::vector<Player *> &players, std::vector<Monster *> &monsters,
             std::vector<Platform *> &platforms, std::vector<GameObject *> &other); // constructor
    void Draw(Camera2D sceneCamera); // draw call
    ~Renderer(); // destructor
};


#endif //PLATFORMER_RENDERER_H
