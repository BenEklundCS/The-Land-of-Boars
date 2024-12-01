//
// Created by luke4 on 11/25/2024.
//

#include "../../../include/Game/Entities/uiElements/HealthBar.h"

#include "../../../../include/Game/Management/GameStateManager.h"
#include "../../../../include/Game/Sprites/TextureManager.h"

#define HEALTH_BAR_WIDTH 50
#define HEALTH_BAR_HEIGHT 50

HealthBar::HealthBar(float pos_x, float pos_y, int hp) {
    // Set position and dimensions
    position_ = Vector2{pos_x, pos_y};
    dimensions_ = Vector2{HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT}; // Use constants for consistent size
    hp_ = hp;
    // Load texture from the TextureManager
    gameTexture_ = TextureManager::GetInstance()->GetTexture(HEALTH_GLOBE_TEXTURE);
}




void HealthBar::Update() {
    auto camera = GameStateManager::GetInstance()->GetCamera();
    // Anchor to the top-left corner of the screen relative to the camera
    position_.x = camera.target.x - camera.offset.x + 5;
    position_.y = camera.target.y - camera.offset.y + 5;
    hp_ = GameStateManager::GetInstance()->GetPlayers().at(0)->GetPlayerData()->hp_; // update hp
}


void HealthBar::Draw() {
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
}



