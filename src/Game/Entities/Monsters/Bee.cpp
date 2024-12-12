//
// Created by ben on 10/8/24.
//

#include "../../../../include/Game/Entities/Monsters/Bee.h"
#include "../../../../include/Game/Management/GameStateManager.h"


// Bee constructor
Bee::Bee(const float posX, const float posY, const float dimX, const float dimY, const MonsterState state)
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
    const Texture2D beeTexture = beeAnimation_->GetTexture();
    const Rectangle currentRect = beeAnimation_->GetCurrentRect();
    beeAnimation_->FlipX(!movingRight_);
    // Draw the boar utilizing the currently loaded boarTexture, and rect position
    DrawTexturePro(beeTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

// Update the bee
void Bee::Update() {
    AnimateBee();
    if (state_ != DYING) { // do not allow state transition if dying
        if (InAttackRange()) {
            state_ = MOVE_TO_FLYING;
        } else {
            state_ = MOVE_TO_FLYING;
        }
    }
    Monster::Update();
}

// Logic to call when the bee dies
void Bee::Died() {
    shouldRemove_ = true;
}

int counter = 0;

bool Bee::InAttackRange() {
    // Get player from the GameStateManager

    auto players = GameStateManager::GetInstance()->GetPlayers();
    // Get relevant object positions
    Vector2 playerPosition = players.at(0)->GetPosition(); // get player1's position
    Vector2 beePosition = position_;
    
    if (std::abs(playerPosition.x - beePosition.x) < 50.0f || std::abs(playerPosition.y - beePosition.y) < 50.0f) {
        return true;
    }
    return false; // dummy return for now
}

// Animate the bee
void Bee::AnimateBee() {
    beeAnimation_->Animate();
    if (state_ == DYING && beeAnimation_->IsDone()) {
        TraceLog(LOG_INFO, "BEE HAS DIED");
        Died();
    }
}

// Override of hit monster
void Bee::HitMonster(const int damage) {
    Monster::HitMonster(damage);
    if (GetHealth() <= 0) {
        BeginDeathAnimation(); // play the death animation, then set shouldRemove_ to true after it fully plays
        Notify(this, EVENT_BEE_DIED);
    }
    else {
        Notify(this, EVENT_BEE_HIT); // Notify the boar has been hit, but didn't die
    }
}

void Bee::BeginDeathAnimation() {
    if (state_ != DYING) {
        state_ = DYING;
        beeAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BEE_DYING_TEXTURE), BEE_DYING_FRAMES, 0.10f, false);
    }
}