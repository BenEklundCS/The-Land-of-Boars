//
// Created by ben on 5/25/24.
//

#include "Boar.h"

Boar::Boar(float posX, float posY, float dimX, float dimY, MonsterState state)
: Monster(posX, posY, dimX, dimY, state),
boarAnimation_(TextureManager::GetInstance()->GetTexture(BOAR_RUNNING_TEXTURE_WHITE), BOAR_RUNNING_FRAMES, 0.2f, true) {}

void Boar::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    Texture2D monsterTexture = boarAnimation_.GetTexture();
    Rectangle currentRect = boarAnimation_.GetCurrentRect();
    boarAnimation_.FlipX(movingRight_); // flip x axis based on the movingRight_ flag
    // Draw the player utilizing the currently loaded playerTexture, and rect position
    DrawTexturePro(monsterTexture, currentRect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

