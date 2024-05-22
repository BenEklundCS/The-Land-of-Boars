//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Window.h"
#include "../Entities/GameObject.h"

#ifndef PLATFORMER_RENDERER_H
#define PLATFORMER_RENDERER_H

class Renderer {
private:
    static void RenderBackground();
public:
    Renderer(); // constructor
    static void Draw(const std::vector<GameObject*>& objects); // draw call
    ~Renderer(); // destructor
};


#endif //PLATFORMER_RENDERER_H
