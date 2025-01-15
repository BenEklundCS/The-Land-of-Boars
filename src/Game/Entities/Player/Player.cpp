//
// Created by ben on 5/17/24.
//

#include "../../../../include/Game/Entities/Player/Player.h"
#include "../../../../include/Game/Management/GameStateManager.h"
#include "../../../include/Utilities/Thread.h"
#include <thread>

// Player state management
// Each state has an associated animation
// States: IDLE, RUNNING, JUMPING, ATTACKING
// Player is IDLE at the start of the game
// Player becomes RUNNING if they move left or right, and are not JUMPING
// Player becomes JUMPING when a Jump method is called, they should remain in a JUMPING state until they hit the ground again
// Player becomes ATTACKING when an Attack method is called, no matter what they should remain attacking until the attack method finishes

/**
 * @brief Player constructor.
 *
 * Initializes the player object with default attributes such as position, dimensions, animations, and health bar.
 * The player starts in the `IDLE` state.
 */
Player::Player() : GameObject(PLAYER) {
    // Construct the primitive GameObject attributes
    position_ = Vector2{300, -300 };
    dimensions_ = Vector2{PLAYER_LENGTH, PLAYER_LENGTH};
    // Scale the object
    Scale();
    // Load it here to ensure the TextureManager is queried after the player object is created
    playerData.playerAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(PLAYER_IDLE_TEXTURE),
                                                              PLAYER_IDLE_FRAMES, 0.2f, true);
    playerUI_ = std::make_unique<PlayerUI>(150, 150, 100, 0);
}

#pragma region render methods

/**
 * @brief Draws the player on the screen.
 *
 * This method retrieves the current animation frame and renders the player.
 * If the game is in `MODE_GAME`, the health bar is also drawn.
 */
void Player::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object

    const Texture2D playerTexture = playerData.playerAnimation_->GetTexture();
    const Rectangle currentRect = playerData.playerAnimation_->GetCurrentRect();
    if (GameStateManager::GetInstance()->GetMode() == MODE_GAME)
        playerUI_->Draw();
    // Draw the player utilizing the currently loaded playerTexture, and rect position
    DrawTexturePro(playerTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

/**
 * @brief Updates the player's state and attributes.
 *
 * Handles state transitions, animations, movement, and health bar updates.
 * Also ensures the player's jump counter and attack state are managed correctly.
 */
void Player::Update() {
    // Get deltaTime
    const float deltaTime = GetFrameTime();
    // State
    StateTransition();
    // Check to see if we need to update the displayed animation
    AnimatePlayer();
    // Reset Jumps
    ResetJumps();
    // Move the player based on their velocity and position
    MovePlayer(deltaTime);
    GameObject::Update();
    // Update PlayerUI
    playerUI_->Update();
    playerData.timeSinceLastAttack_ += deltaTime;
    playerData.last_state_ = playerData.state_;
}

#pragma endregion

#pragma region movement methods

/**
 * @brief Moves the player based on velocity and physics.
 *
 * This method applies gravity, friction, and updates the player's position.
 *
 * @param deltaTime Time elapsed since the last frame.
 */
void Player::MovePlayer(const float deltaTime) {
    // Call the updatePosition and velocity changing functions
    GameObject::ApplyFriction();
    GameObject::ApplyGravity();
    UpdatePosition(deltaTime);
}

/**
 * @brief Updates the player's position based on velocity.
 *
 * @param deltaTime Time elapsed since the last frame.
 */
void Player::UpdatePosition(const float deltaTime) {
    position_.x += velocity_.x * deltaTime;
    position_.y += velocity_.y * deltaTime;
}

/**
 * @brief Moves the player to the left.
 *
 * Updates the player's state to `RUNNING` and decreases horizontal velocity.
 */
void Player::MoveLeft() {
    // If the player is not also jumping, we'll display the RUNNING animation
    if (velocity_.y == 0 && playerData.state_ != ATTACKING) {
        playerData.state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    movingRight_ = false;
    // Set the player's X velocity
    if (velocity_.x >= -MAX_VELOCITY) {
        velocity_.x -= PLAYER_SPEED_X;
    }
}

/**
 * @brief Moves the player to the right.
 *
 * Updates the player's state to `RUNNING` and increases horizontal velocity.
 */
void Player::MoveRight() {
    // If the player is not also jumping, we'll display the RUNNING animation
    if (velocity_.y == 0 && playerData.state_ != ATTACKING) {
        playerData.state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    movingRight_ = true;
    // Set the player's X velocity
    if (velocity_.x <= MAX_VELOCITY) {
        velocity_.x += PLAYER_SPEED_X;
    }
}

/**
 * @brief Makes the player jump.
 *
 * Updates the player's state to `JUMPING`, increases vertical velocity, and notifies observers of the jump event.
 */
void Player::Jump() {
    if (playerData.jumpTimer_ == 0) {
        // Set isOnGround to false if they jump!
        playerData.isOnGround_ = false;
        // Set jumps and reset player animation
        playerData.jumps_++; // Increment jumps
        playerData.playerAnimation_->Reset(); // Reset the player's animation on Jump (handles double jump animating)
        // Make the player jump!
        playerData.state_ = JUMPING;
        velocity_.y -= PLAYER_SPEED_Y * PLAYER_JUMP_POWER;
        // add to jump delay
        playerData.jumpTimer_ += jumpDelay_;
        // Notify of jump event
        Notify(this, EVENT_PLAYER_JUMPED);
    }
}

#pragma endregion

#pragma region player actions

/**
 * @brief Makes the player attack.
 *
 * Updates the player's state to `ATTACKING` if enough time has passed since the last attack.
 * Notifies observers of the attack event.
 */
void Player::Attack() {
    // Set the player's state to ATTACKING if enough time has elapsed
    if (playerData.timeSinceLastAttack_ > PLAYER_ATTACK_DELAY) {
        playerData.state_ = ATTACKING;
        playerData.timeSinceLastAttack_ = 0.0f;
        Notify(this, EVENT_PLAYER_ATTACK); // Notify relevant observers the player has attacked
    }
    // Else maybe we notify of a failed attack to play a sound
}

#pragma endregion

#pragma region player state/animations

/**
 * @brief Updates the player's animation and transitions between states.
 */
void Player::AnimatePlayer() {
    // Call Animate to get the next rect
    playerData.playerAnimation_->Animate();
    // If we're currently attacking, don't transition in the code below until the attack is over
    if (AlreadyAttacking()) {
        return;
    }

    // Check to see if we need to load a new animation to playerAnimation_
    // We need to load a new animation if state_ != last_state_
    if (playerData.state_ != playerData.last_state_) {
        LoadNewAnimation();
    }

    // Flip animation after loading based on the movingRight_ flag
    playerData.playerAnimation_->FlipX(movingRight_);
}

/**
 * @brief Loads a new animation based on the player's current state.
 */
void Player::LoadNewAnimation() {
    // Changing state, so get the TextureManager so we can load the next animation
    TextureManager* textureManager = TextureManager::GetInstance();

    float idleAnimationSpeed = 0.2f;
    float runningAnimationSpeed = 0.2f;
    float jumpingAnimationSpeed = 0.075f;
    float playerAttackingSpeed = 0.05f;

    switch (playerData.state_) {
        // Invoke the Animation constructor to load a new animation with the desired state, and properties
        // replay the idle animation (replay == true) or false if you do not want replay
        case IDLE:
            playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_IDLE_TEXTURE), PLAYER_IDLE_FRAMES, idleAnimationSpeed, true);
            break;
        case RUNNING:
            playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_RUNNING_TEXTURE), PLAYER_RUNNING_FRAMES, runningAnimationSpeed, true);
            break;
        case JUMPING:
            playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_JUMPING_TEXTURE), PLAYER_JUMPING_FRAMES, jumpingAnimationSpeed, false);
            break;
        case ATTACKING:
            playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_ATTACKING_TEXTURE), PLAYER_ATTACKING_FRAMES, playerAttackingSpeed, false);
            break;
    }
}


/**
 * @brief Transitions the player to the `IDLE` state if applicable.
 */
void Player::StateTransition() {
    if (ZeroVelocity() && (playerData.state_ != ATTACKING)) {
        playerData.state_ = IDLE;
    }
}

/**
 * @brief Checks if the player can jump based on remaining jumps.
 *
 * @return True if the player has no velocity in the x or y direction. False otherwise.
 */
bool Player::ZeroVelocity() const {
    return (velocity_.x == 0 && velocity_.y == 0);
}

/**
 * @brief Checks if the player can jump based on remaining jumps.
 *
 * @return True if the player can jump, false otherwise.
 */
bool Player::CanJump() const {
    return playerData.jumps_ <= PLAYER_MAX_JUMPS;
}

/**
 * @brief Resets the player's jump counter if they are on the ground.
 */
void Player::ResetJumps() {
    if (playerData.jumpTimer_ > 0) {
        playerData.jumpTimer_ -= GetFrameTime();
    } else {
        playerData.jumpTimer_ = 0;
    }
    // If the player's on the ground, reset jumps
    if (playerData.isOnGround_ && playerData.state_ != JUMPING) {
        playerData.jumps_ = 0;
    }
    if (velocity_.y == 0) {
        playerData.isOnGround_ = true;
    }
}

/**
 * @brief Checks if the player is currently attacking.
 *
 * @return True if the player is in the `ATTACKING` state, false otherwise.
 */
bool Player::AlreadyAttacking() {
    if (playerData.state_ == ATTACKING && playerData.last_state_ == ATTACKING) {
        if (playerData.playerAnimation_->IsDone()) {
            playerData.state_ = IDLE; // Set IDLE here to ensure we go idle when the player is actually done attacking
            return false;
        }
        else {
            return true;
        }
    }
    return false;
}

#pragma endregion

#pragma region player object interactions

/**
 * @brief Handles player being hit, reducing HP and notifying observers.
 */
void Player::HitPlayer() {
    // 1 second safety window
    if (playerData.timeSinceHit_ > 1.0f) {
        GameObject::ToggleFlashing();
        playerData.hp_ -= 1;
        if (CheckPlayerDeath()) {
            // Player has died
            Notify(this, EVENT_PLAYER_DIED);
            // Use a thread to call a function on a delay using Thread.h
            callAfterDelay([]() {
                GameStateManager::GetInstance()->SetLevelOver(); // set level over after a 1350ms delay
            }, 1350); // Sets level over to True, ending the game
        }
        else {
            // Player was hit but has not died
            Notify(this, EVENT_PLAYER_HIT);
        }
    }
}

/**
 * @brief Checks if the player is dead.
 *
 * @return True if the player's HP is 0 or less, false otherwise.
 */
bool Player::CheckPlayerDeath() const {
    return playerData.hp_ <= 0;
}

/**
 * @brief Returns a pointer to the player's data.
 *
 * @return Pointer to the player's data structure.
 */
playerDataStruct* Player::GetPlayerData() {
    playerData.timeSinceHit_ = timeSinceToggle_;
    return &playerData;
}

#pragma endregion
