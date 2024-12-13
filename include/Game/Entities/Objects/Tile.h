//
// Created by ben on 5/29/24.
//

#ifndef PLATFORMER_TILE_H
#define PLATFORMER_TILE_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"

/**
 * @file Tile.h
 * @brief Defines the Tile class, representing a tile object in the platformer game.
 *
 * This class allows for creating and rendering a tile object in the game. Each tile
 * has a texture and can be drawn or updated within the game world.
 */

/**
 * @class Tile
 * @brief Represents a tile in the platformer game.
 *
 * The Tile class inherits from GameObject and is responsible for storing and rendering
 * a tile's texture at a specific position in the game world. It provides methods to
 * update and draw the tile during each game frame.
 */
class Tile : public GameObject {
private:
    GameTexture texture_; ///< The texture applied to the tile.

public:
    /**
     * @brief Constructs a Tile object with a specific position and texture.
     *
     * Initializes the tile at the given coordinates and applies the provided texture.
     *
     * @param x The x-coordinate of the tile.
     * @param y The y-coordinate of the tile.
     * @param tileTexture The texture name for the tile.
     */
    Tile(float x, float y, TextureName tileTexture);

    /**
     * @brief Draws the tile on the screen.
     *
     * This method overrides the base class's Draw method to render the tile's texture
     * at the specified position.
     */
    void Draw() override;

    /**
     * @brief Updates the state of the tile.
     *
     * This method overrides the base class's Update method. For tiles, this could be used
     * to handle behaviors such as animation or interactions.
     */
    void Update() override;

    /**
     * @brief Sets the texture for the tile.
     *
     * This method allows the tile to change its texture dynamically.
     *
     * @param texture The new texture to apply to the tile.
     */
    [[maybe_unused]] void SetTexture(const GameTexture &texture);
};

#endif //PLATFORMER_TILE_H
