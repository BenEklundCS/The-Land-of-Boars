//
// Created by luke4 on 12/17/2024.
//

#ifndef COIN_H
#define COIN_H

//
// Created by ben on 8/4/24.
//

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"

/**
 * @file Coin.h
 * @brief Defines the Coin class, representing a coin object in the platformer game.
 *
 * This class allows for creating and rendering a coin object in the game, including
 * associating a texture and updating its state.
 */

/**
 * @class Coin
 * @brief Represents a coin object in the platformer game.
 *
 * This class inherits from GameObject and manages a coin’s texture, drawing it on screen,
 * and updating its state. It allows coin to be part of the game world, interacting
 * with other objects in the game.
 */
class Coin : public GameObject {
private:
    GameTexture texture_; ///< The texture applied to the coin.

public:
    /**
     * @brief Constructs a Coin object with a specific position and texture.
     *
     * Initializes the coin at the given coordinates and applies the provided texture.
     *
     * @param x The x-coordinate for the coin.
     * @param y The y-coordinate for the coin.
     */
    Coin(float x, float y);

    /**
     * @brief Draws the coin object on the screen.
     *
     * This method overrides the base class's Draw method to render the coin's texture
     * at the specified position.
     */
    void Draw() override;

    /**
     * @brief Updates the state of the coin object.
     *
     * This method overrides the base class's Update method, allowing for any
     * specific coin behavior or state changes (e.g., animations, interactions).
     */
    void Update() override;
};

#endif //COIN_H
