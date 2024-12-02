//
// Created by ben on 11/1/24.
//

#include "../../../include/Game/Entities/Monsters/Snail.h"

Snail::Snail(const float posX, const float posY, const float dimX, const float dimY, const MonsterState state)
        : Monster(posX, posY, dimX, dimY, state) {
    // Scale the snail before loading the animation
    Scale();
    // Load the snail animation
    snailAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(SNAIL_TEXTURE), SNAIL_FRAMES, 0.1f, true);
    this->hp_ = SNAIL_MAX_HEALTH;
}

void Snail::Draw() {
    const Texture2D snailTexture = snailAnimation_->GetTexture();
    const Rectangle currentRect = snailAnimation_->GetCurrentRect();
    snailAnimation_->FlipX(!movingRight_);
    DrawTexturePro(snailTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);
}

void Snail::Update() {
    AnimateSnail();
    Monster::Update();
}

void Snail::Died() {
    // Implementation for when Snail dies
    shouldRemove_ = true;
}

void Snail::BeginDeathAnimation() {
    if (state_ != DYING) {
        state_ = DYING;
        snailAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(SNAIL_DYING_TEXTURE), SNAIL_DYING_FRAMES, 0.10f, false);
    }
}

void Snail::AnimateSnail() {
    snailAnimation_->Animate();
    if (state_ == DYING && snailAnimation_->IsDone()) {
        Died();
    }
}

void Snail::HitMonster(const int damage) {
    Monster::HitMonster(damage);
    if (GetHealth() <= 0) {
        BeginDeathAnimation(); // play the death animation, then set shouldRemove_ to true after it fully plays
        Notify(this, EVENT_SNAIL_DIED);
    }
    else {
        Notify(this, EVENT_SNAIL_HIT); // Notify the boar has been hit, but didn't die
    }
}
