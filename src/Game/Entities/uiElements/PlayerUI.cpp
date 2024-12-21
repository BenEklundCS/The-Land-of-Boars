//
// Created by luke4 on 11/25/2024.
//

#include "../../../include/Game/Entities/uiElements/PlayerUI.h"

#include "../../../../include/Game/Management/GameStateManager.h"
#include "../../../../include/Game/Sprites/TextureManager.h"

#define HEALTH_BAR_WIDTH 50
#define HEALTH_BAR_HEIGHT 50

/**
 * @brief Constructs a HealthBar object.
 *
 * Initializes the health bar at a specified position with the player's current HP
 * and loads the health globe texture from the TextureManager.
 *
 * @param pos_x The x-coordinate for the health bar's initial position.
 * @param pos_y The y-coordinate for the health bar's initial position.
 * @param hp The initial HP value to display.
 */
PlayerUI::PlayerUI(float pos_x, float pos_y, int hp, int coins) {
    // Set position and dimensions
    position_ = Vector2{pos_x, pos_y};
    dimensions_ = Vector2{HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT}; // Use constants for consistent size
    hp_ = hp;
    coins_ = coins;
    // Load texture from the TextureManager
    gameTexture_ = TextureManager::GetInstance()->GetTexture(HEALTH_GLOBE_TEXTURE);
}

/**
 * @brief Updates the health bar's position and current health.
 *
 * The health bar is anchored to the top-left corner of the screen relative to the camera,
 * and its health value (`hp_`) is updated from the player's current HP in the GameStateManager.
 */
void PlayerUI::Update() {
    auto camera = GameStateManager::GetInstance()->GetCamera();
    // Anchor to the top-left corner of the screen relative to the camera
    position_.x = camera.target.x - camera.offset.x + 5;
    position_.y = camera.target.y - camera.offset.y + 5;
    hp_ = GameStateManager::GetInstance()->GetPlayers().at(0)->GetPlayerData()->hp_; // update hp
    coins_ = GameStateManager::GetInstance()->GetPlayers().at(0)->GetPlayerData()->coins_; // update coins
}

/**
 * @brief Draws the health bar on the screen.
 *
 * Each health globe is rendered as a part of the health bar using the loaded texture.
 * The globes are spaced evenly with a 5-pixel gap between them.
 */
void PlayerUI::Draw() {
    // Use the loaded texture and rectangles for rendering
    for (int i = 0; i < hp_; i++) {
        Rectangle destRect = GetRect();
        destRect.x += i * (HEALTH_BAR_WIDTH + 5); // Adjust x position for each globe, with a 5-pixel gap
        DrawTexturePro(
            gameTexture_.texture,            // Texture
            gameTexture_.rect,               // Source rectangle (entire texture or portion)
            destRect,                        // Destination rectangle (position and size on screen)
            Vector2{0, 0},               // Origin (top-left corner)
            0,                               // Rotation
            WHITE                            // Color tint
        );
    }

    auto camera = GameStateManager::GetInstance()->GetCamera();
    DrawText(TextFormat("Coins: %d", coins_), camera.target.x - camera.offset.x + GetScreenWidth() - MeasureText(TextFormat("Coins: %d", coins_), 20) - 20, camera.target.y - camera.offset.y + 5, 20, YELLOW);
}



