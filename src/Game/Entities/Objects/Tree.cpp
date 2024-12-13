//
// Created by ben on 8/4/24.
//
#include "../../../../include/Game/Entities/Objects/Tree.h"

/**
 * @brief Constructs a Tree object.
 *
 * Initializes the tree's position, dimensions, and texture. The tree is scaled based on the window scale factor.
 *
 * @param x X-coordinate of the tree.
 * @param y Y-coordinate of the tree.
 * @param treeTexture The texture to use for the tree, loaded via the TextureManager.
 */
Tree::Tree(const float x, const float y, const TextureName treeTexture) : GameObject(TREE),
                                                                          texture_(TextureManager::GetInstance()->GetTexture(treeTexture)) {
    // Ensure to instantiate the GameObject!
    dimensions_ = Vector2{TREE_WIDTH, TREE_HEIGHT};
    position_ = Vector2{x, y};
    // Scale the game object
    Scale();
}

/**
 * @brief Updates the tree object.
 *
 * Currently, the tree has no update logic, but this method is included to adhere to the GameObject interface.
 */
void Tree::Update() {

}

/**
 * @brief Draws the tree on the screen.
 *
 * The texture is drawn using the tree's position and dimensions, scaled appropriately.
 */
void Tree::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw the texture
}


