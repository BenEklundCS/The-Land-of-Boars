//
// Created by ben on 11/1/24.
//

#include "../../../include/Game/Entities/Monsters/Snail.h"

/**
 * @brief Constructs a Snail object with specified position, dimensions, and initial state.
 *
 * The Snail is initialized with its animation and health points.
 *
 * @param posX The x-coordinate of the Snail's position.
 * @param posY The y-coordinate of the Snail's position.
 * @param dimX The width of the Snail.
 * @param dimY The height of the Snail.
 * @param state The initial state of the Snail.
 */
Snail::Snail(const float posX, const float posY, const float dimX, const float dimY, const MonsterState state)
        : Monster(posX, posY, dimX, dimY, state) {
    // Scale the snail before loading the animation
    Scale();
    // Load the snail animation
    snailAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(SNAIL_TEXTURE), SNAIL_FRAMES, 0.1f, true);
    this->hp_ = SNAIL_MAX_HEALTH;
}

/**
 * @brief Renders the Snail to the screen using its current animation frame.
 */
void Snail::Draw() {
    const Texture2D snailTexture = snailAnimation_->GetTexture();
    const Rectangle currentRect = snailAnimation_->GetCurrentRect();
    snailAnimation_->FlipX(!movingRight_);
    DrawTexturePro(snailTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);
}

/**
 * @brief Updates the Snail's animation and other game logic.
 */
void Snail::Update() {
    AnimateSnail();
    Monster::Update();
}

/**
 * @brief Begins the Snail's death animation if not already in the DYING state.
 */
void Snail::BeginDeathAnimation() {
    if (state_ != DYING) {
        state_ = DYING;
        snailAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(SNAIL_DYING_TEXTURE), SNAIL_DYING_FRAMES, 0.10f, false);
    }
}

/**
 * @brief Animates the Snail based on its current state.
 *
 * If the Snail is in the DYING state and the animation finishes, the Snail is marked as dead.
 */
void Snail::AnimateSnail() {
    snailAnimation_->Animate();
    if (state_ == DYING && snailAnimation_->IsDone()) {
        Died();
    }
}

/**
 * @brief Handles when the Snail is hit by an attack.
 *
 * Reduces the Snail's health by the specified damage amount. If the Snail's health reaches 0,
 * it transitions to the DYING state and plays the death animation. Notifies observers of the Snail's state.
 *
 * @param damage The amount of damage dealt to the Snail.
 */
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
