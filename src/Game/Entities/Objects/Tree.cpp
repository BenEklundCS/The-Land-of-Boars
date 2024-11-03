//
// Created by ben on 8/4/24.
//
#include "../../../../include/Game/Entities/Objects/Tree.h"

Tree::Tree(float x, float y, TextureName treeTexture) : GameObject(TREE),
    texture_(TextureManager::GetInstance()->GetTexture(treeTexture)) {
    // Ensure to instantiate the GameObject!
    dimensions_ = Vector2{TREE_WIDTH, TREE_HEIGHT};
    position_ = Vector2{x, y};
    // Scale the game object
    Scale();
}

void Tree::Update() {

}

void Tree::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw the texture
}


