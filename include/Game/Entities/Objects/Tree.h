//
// Created by ben on 8/4/24.
//


#ifndef PLATFORMER_TREE_H
#define PLATFORMER_TREE_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"

// Tree Measurements
#define TREE_WIDTH 400
#define TREE_HEIGHT 1000

/**
 * @file Tree.h
 * @brief Defines the Tree class, representing a tree object in the platformer game.
 *
 * This class allows for creating and rendering a tree object in the game, including
 * associating a texture and updating its state.
 */

/**
 * @class Tree
 * @brief Represents a tree object in the platformer game.
 *
 * This class inherits from GameObject and manages a tree’s texture, drawing it on screen,
 * and updating its state. It allows trees to be part of the game world, interacting
 * with other objects in the game.
 */
class Tree : public GameObject {
private:
    GameTexture texture_; ///< The texture applied to the tree.

public:
    /**
     * @brief Constructs a Tree object with a specific position and texture.
     *
     * Initializes the tree at the given coordinates and applies the provided texture.
     *
     * @param x The x-coordinate for the tree.
     * @param y The y-coordinate for the tree.
     * @param treeTexture The texture name for the tree.
     */
    Tree(float x, float y, TextureName treeTexture);

    /**
     * @brief Draws the tree object on the screen.
     *
     * This method overrides the base class's Draw method to render the tree's texture
     * at the specified position.
     */
    void Draw() override;

    /**
     * @brief Updates the state of the tree object.
     *
     * This method overrides the base class's Update method, allowing for any
     * specific tree behavior or state changes (e.g., animations, interactions).
     */
    void Update() override;
};

#endif //PLATFORMER_TREE_H
