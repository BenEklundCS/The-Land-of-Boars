//
// Created by ben on 10/8/24.
//

#include "../../../../include/Game/Entities/Monsters/Bee.h"
#include "../../../../include/Game/Management/GameStateManager.h"


/**
 * @brief Constructs a Bee object with the specified position, dimensions, and state.
 *
 * Initializes the Bee's animation, health, and scale.
 *
 * @param posX The x-coordinate of the Bee's position.
 * @param posY The y-coordinate of the Bee's position.
 * @param dimX The width of the Bee.
 * @param dimY The height of the Bee.
 * @param state The initial state of the Bee.
 */
Bee::Bee(const float posX, const float posY, const float dimX, const float dimY, const MonsterState state)
: Monster(posX, posY, dimX, dimY, state) {
    // Scale the bee
    Scale();
    // Load the bee animation
    beeAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BEE_FLYING_TEXTURE), BEE_FLYING_FRAMES, 0.1f, true);
    this->hp_ = BEE_MAX_HEALTH;
}

/**
 * @brief Draws the Bee to the screen.
 *
 * Uses the Bee's animation and position to render its current state.
 */
void Bee::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    const Texture2D beeTexture = beeAnimation_->GetTexture();
    const Rectangle currentRect = beeAnimation_->GetCurrentRect();
    beeAnimation_->FlipX(!movingRight_);
    // Draw the boar utilizing the currently loaded boarTexture, and rect position
    DrawTexturePro(beeTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

/**
 * @brief Updates the Bee's behavior and animation.
 *
 * Handles animation, state transitions, and updates from the base Monster class.
 */
void Bee::Update() {
    AnimateBee();
    if (state_ != DYING) { // do not allow state transition if dying
        if (InAttackRange()) {
            state_ = MOVE_TO_FLYING;
        } else {
            state_ = DEFAULT;
        }
    }
    Monster::Update();
}

int counter = 0;

/**
 * @brief Checks if the Bee is within attack range of the player.
 *
 * Calculates the distance between the Bee and the player to determine if it is close enough to attack.
 *
 * @return True if the Bee is within attack range, false otherwise.
 */
bool Bee::InAttackRange() const {
    // Get player from the GameStateManager

    const auto players = GameStateManager::GetInstance()->GetPlayers();
    // Get relevant object positions
    auto [player_x, player_y] = players.at(0)->GetPosition(); // get player1's position

    if (auto [bee_x, bee_y] = position_; std::abs(player_x - bee_x) < 50.0f || std::abs(player_y - bee_y) < 50.0f) {
        return true;
    }
    return false; // dummy return for now
}

/**
 * @brief Animates the Bee.
 *
 * Updates the Bee's animation and handles the death animation completion.
 */
void Bee::AnimateBee() {
    beeAnimation_->Animate();
    if (state_ == DYING && beeAnimation_->IsDone()) {
        Died();
    }
}

/**
 * @brief Handles the Bee being hit.
 *
 * Reduces the Bee's health and notifies observers. If the health drops to zero, triggers the death animation.
 *
 * @param damage The amount of damage dealt to the Bee.
 */
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

/**
 * @brief Initiates the Bee's death animation.
 */
void Bee::BeginDeathAnimation() {
    if (state_ != DYING) {
        state_ = DYING;
        beeAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(BEE_DYING_TEXTURE), BEE_DYING_FRAMES, 0.10f, false);
    }
}