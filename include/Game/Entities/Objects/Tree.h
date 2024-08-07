//
// Created by ben on 8/4/24.
//

#ifndef PLATFORMER_TREE_H
#define PLATFORMER_TREE_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"

class Tree : public GameObject {
private:
    GameTexture texture_;
public:
    Tree(float x, float y, const std::string& treeTexture);
    void Draw() override;
    void Update() override;
};

#endif //PLATFORMER_TREE_H
