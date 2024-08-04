//
// Created by ben on 8/4/24.
//
#include "../../../../include/Game/Entities/Objects/Tree.h"

Tree::Tree(float x, float y, std::string treeTexture) : GameObject(TREE), texture_(TextureManager::GetInstance()->GetTexture(treeTexture))
{ // Ensure to instantiate the GameObject!
    dimensions_ = Vector2{TILE_LENGTH, TILE_LENGTH};
    position_ = Vector2{x, y};
}

void Tree::Update() {

}

void Tree::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw the texture
}


