//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Window.h"
#include "../Game/Management/GameStateManager.h"


#ifndef PLATFORMER_RENDERER_H
#define PLATFORMER_RENDERER_H

/*
 * The Renderer takes a pointer to a GameStateManager to draw the gameState
*/
class Renderer {
private:
    static void RenderBackground();
public:
    Renderer(); // constructor
    static void Draw(GameStateManager* gameState); // draw call
    ~Renderer(); // destructor
};


#endif //PLATFORMER_RENDERER_H
