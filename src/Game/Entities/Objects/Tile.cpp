//
// Created by ben on 5/29/24.
//

#include "../../../../include/Game/Entities/Objects/Tile.h"

/**
 * @brief Constructs a Tile object.
 *
 * Initializes the tile's position, dimensions, and texture. The tile is scaled based on the window scale factor.
 *
 * @param x X-coordinate of the tile.
 * @param y Y-coordinate of the tile.
 * @param tileTexture The texture to use for the tile, loaded via the TextureManager.
 */
Tile::Tile(const float x, const float y, const TextureName tileTexture) : GameObject(TILE) {
    // Ensure to instantiate the GameObject!
    dimensions_ = Vector2{TILE_LENGTH, TILE_LENGTH};
    position_ = Vector2{x, y};
    // Scale the game object
    Scale();
    // Load the texture
    texture_ = TextureManager::GetInstance()->GetTexture(tileTexture);
}

/**
 * @brief Draws the tile on the screen.
 *
 * Uses the loaded texture and the tile's position and dimensions for rendering.
 */
void Tile::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw the texture
}

/**
 * @brief Updates the tile object.
 *
 * Currently, the tile has no update logic, but this method is included to adhere to the GameObject interface.
 */
void Tile::Update() {

}

/**
 * @brief Sets a new texture for the tile.
 *
 * @param texture The new texture to assign to the tile.
 */
[[maybe_unused]] void Tile::SetTexture(const GameTexture &texture) {
    texture_ = texture;
}
