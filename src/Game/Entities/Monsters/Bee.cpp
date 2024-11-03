//
// Created by ben on 10/8/24.
//

#include "../../../../include/Game/Entities/Monsters/Bee.h"


// Bee constructor
Bee::Bee(float posX, float posY, float dimX, float dimY, MonsterState state)
: Monster(posX, posY, dimX, dimY, state) {
    // Scale the bee
    Scale();
    // Load the bee animation
    beeAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BEE_FLYING_TEXTURE), BEE_FLYING_FRAMES, 0.1f, true);
    this->hp_ = BEE_MAX_HEALTH;
}

// Draw the bee
void Bee::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    Texture2D beeTexture = beeAnimation_->GetTexture();
    Rectangle currentRect = beeAnimation_->GetCurrentRect();
    beeAnimation_->FlipX(!movingRight_);
    // Draw the boar utilizing the currently loaded boarTexture, and rect position
    DrawTexturePro(beeTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

// Update the bee
void Bee::Update() {
    AnimateBee();
    Monster::Update();
}

// Logic to call when the bee dies
void Bee::Died() {

}

// Animate the bee
void Bee::AnimateBee() {
    beeAnimation_->Animate();
}

// Override of hit monster
void Bee::HitMonster(int damage) {
    Monster::HitMonster(damage);
}