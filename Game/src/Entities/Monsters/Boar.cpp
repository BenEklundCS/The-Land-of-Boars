//
// Created by ben on 5/25/24.
//

#include "../../../include/Boar.h"

Boar::Boar(float posX, float posY, float dimX, float dimY, MonsterState state)
: Monster(posX, posY, dimX, dimY, state),
boarAnimation_(TextureManager::GetInstance()->GetTexture(BOAR_RUNNING_TEXTURE_WHITE), BOAR_RUNNING_FRAMES, 0.1f, true) {

}

void Boar::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    Texture2D boarTexture = boarAnimation_.GetTexture();
    Rectangle currentRect = boarAnimation_.GetCurrentRect();
    boarAnimation_.FlipX(!movingRight_); // flip x axis based on the INVERSE of this flag, because boars face the opposite way in the sprite sheet
    // Draw the boar utilizing the currently loaded boarTexture, and rect position
    DrawTexturePro(boarTexture, currentRect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void Boar::Update() {
    boarAnimation_.Animate();
    Monster::Update();
}

