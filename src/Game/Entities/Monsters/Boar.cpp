//
// Created by ben on 5/25/24.
//



#include "../../../../include/Game/Entities/Monsters/Boar.h"
#include <stdlib.h>     /* srand, rand */

Boar::Boar(float posX, float posY, float dimX, float dimY, MonsterState state)
: Monster(posX, posY, dimX, dimY, state),
boarAnimation_(std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BOAR_RUNNING_TEXTURE_WHITE), BOAR_RUNNING_FRAMES, 0.1f, true)) {
    this->hp_ = BOAR_MAX_HEALTH;
}

#pragma region render methods

void Boar::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    Texture2D boarTexture = boarAnimation_->GetTexture();
    Rectangle currentRect = boarAnimation_->GetCurrentRect();
    boarAnimation_->FlipX(!movingRight_); // flip x axis based on the INVERSE of this flag, because boars face the opposite way in the sprite sheet
    // Draw the boar utilizing the currently loaded boarTexture, and rect position
    DrawTexturePro(boarTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void Boar::Update() {
    AnimateBoar();
    Monster::Update();
    timeSinceLastOink_ += GetFrameTime();
    MaybeOink();
}

void Boar::HitMonster(int damage) {
    // Run the base class code that's reusable
    Monster::HitMonster(damage);
    // Boar has died
    if (GetHealth() <= 0) {
        BeginDeathAnimation(); // play the death animation, then set shouldRemove_ to true after it fully plays
    }

    Notify(this, EVENT_BOAR_HIT); // Notify the boar has been hit, but didn't die

}

void Boar::BeginDeathAnimation() {
    state_ = DYING;
    // load boar dying animation here
    boarAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BOAR_DYING_TEXTURE_WHITE), BOAR_DYING_FRAMES, 0.10f, false);
}

void Boar::Died() {
    shouldRemove_ = true;
    Notify(this, EVENT_BOAR_DIED); // Notify the boar has died, observers can listen for this event
}

void Boar::AnimateBoar() {
    boarAnimation_->Animate();
    if (state_ == DYING && boarAnimation_->IsDone()) {
        Died();
    }
}

void Boar::MaybeOink() {
    if (timeSinceLastOink_ >= nextOinkTime_) { // Check if the time for the next oink has passed
        Notify(this, EVENT_BOAR_OINKED);
        timeSinceLastOink_ = 0.0f; // Reset the timer
        nextOinkTime_ = (float)(rand() % 30) + 1; // Set the time for the next oink to a random value between 1 and 30 seconds
    }
}

#pragma endregion

