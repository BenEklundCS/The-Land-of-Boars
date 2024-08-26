//
// Created by ben on 5/16/24.
//

#ifndef PLATFORMER_RENDERER_H
#define PLATFORMER_RENDERER_H

#include <vector>
#include "Window.h"
#include "raylib.h"
#include "Engine.h"

struct EngineSettings;
class GameStateManager;

/*
 * The Renderer takes a pointer to a GameStateManager to draw the gameState
*/

class Renderer {
private:
    static void RenderBackground(Camera2D camera);
    static void RenderFPS(Camera2D camera);
public:
    Renderer(); // constructor
    static void Draw(GameStateManager* gameState, EngineSettings* settings); // draw call
    ~Renderer(); // destructor
};


#endif //PLATFORMER_RENDERER_H
