//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Window.h"
#include "../../Game/include/Entities/GameObject.h"
#include "../../Game/include/Entities/Objects/Platform.h"
#include "../../Game/include/Entities/Monsters/Monster.h"
#include "../../Game/include/GameStateManager.h"


#ifndef PLATFORMER_RENDERER_H
#define PLATFORMER_RENDERER_H

class Renderer {
private:
    static void RenderBackground();
public:
    Renderer(); // constructor
    static void Draw(GameStateManager* scene); // draw call
    ~Renderer(); // destructor
};


#endif //PLATFORMER_RENDERER_H
