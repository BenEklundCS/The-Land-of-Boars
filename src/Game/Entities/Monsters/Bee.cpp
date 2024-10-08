//
// Created by ben on 10/8/24.
//

#include "../../../../include/Game/Entities/Monsters/Bee.h"


Bee::Bee(float posX, float posY, float dimX, float dimY, MonsterState state)
: Monster(posX, posY, dimX, dimY, state),
beeAnimation_(std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BEE_FLYING_TEXTURE), BEE_FLYING_FRAMES, 0.1f, true)) {
    this->hp_ = BEE_MAX_HEALTH;
}

void Bee::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    Texture2D beeTexture = beeAnimation_->GetTexture();
    Rectangle currentRect = beeAnimation_->GetCurrentRect();
    beeAnimation_->FlipX(!movingRight_);
    // Draw the boar utilizing the currently loaded boarTexture, and rect position
    DrawTexturePro(beeTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void Bee::Update() {
    AnimateBee();
    Monster::Update();
}

void Bee::Died() {

}

void Bee::AnimateBee() {
    beeAnimation_->Animate();
}

void Bee::HitMonster(int damage) {
    Monster::HitMonster(damage);
}


