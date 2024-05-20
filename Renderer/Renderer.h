//
// Created by ben on 5/16/24.
//

#include <vector>
#include "Window.h"
#include "../Entities/GameObject.h"

#ifndef PLATFORMER_RENDERER_H
#define PLATFORMER_RENDERER_H

class Renderer {
public:
    Renderer();
    static void Draw(const std::vector<GameObject*>& objects);
};


#endif //PLATFORMER_RENDERER_H
