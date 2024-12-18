//
// Created by luke4 on 12/17/2024.
//

#include "../../../../include/Game/Entities/Objects/Coin.h"

#include "../../../../include/Game/Entities/Objects/MovingPlatform.h"
#include "raylib.h"

/**
 * @brief Constructs a Coin object with a specific position and texture.
 *
 * Initializes the coin at the given coordinates and applies the provided texture.
 *
 * @param x The x-coordinate for the coin.
 * @param y The y-coordinate for the coin.
 */
Coin::Coin(float x, float y) : texture_(TextureManager::GetInstance()->GetTexture(COIN_TEXTURE)) {
    position_ = Vector2{x, y};
    dimensions_ = Vector2{COIN_WIDTH, COIN_HEIGHT};
}

/**
 * @brief Draws the coin object on the screen.
 *
 * This method overrides the base class's Draw method to render the coin's texture
 * at the specified position.
 */
void Coin::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, GOLD);     // Draw the texture
}

/**
 * @brief Updates the state of the coin object.
 *
 * This method overrides the base class's Update method, allowing for any
 * specific coin behavior or state changes (e.g., animations, interactions).
 */
void Coin::Update() {

}




