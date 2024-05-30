//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Window.h"
#include "../../Game/include/GameObject.h"
#include "../../Game/include/Platform.h"
#include "../../Game/include/Monster.h"
#include "../../Game/include/Scene.h"


#ifndef PLATFORMER_RENDERER_H
#define PLATFORMER_RENDERER_H

class Renderer {
private:
    static void RenderBackground();
public:
    Renderer(); // constructor
    static void Draw(Scene scene); // draw call
    ~Renderer(); // destructor
};


#endif //PLATFORMER_RENDERER_H
