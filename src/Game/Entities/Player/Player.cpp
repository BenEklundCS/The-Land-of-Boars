//
// Created by ben on 5/17/24.
//

#include "../../../../include/Game/Entities/Player/Player.h"
#include "../../../../include/Game/Entities/Objects/MovingPlatform.h"

// Player state management
// Each state has an associated animation
// States: IDLE, RUNNING, JUMPING, ATTACKING
// Player is IDLE at the start of the game
// Player becomes RUNNING if they move left or right, and are not JUMPING
// Player becomes JUMPING when a Jump method is called, they should remain in a JUMPING state until they hit the ground again
// Player becomes ATTACKING when an Attack method is called, no matter what they should remain attacking until the attack method finishes

Player::Player() : GameObject(PLAYER) {
    // Load it here to ensure the TextureManager is queried after the player object is created
    playerData.playerAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(PLAYER_IDLE_TEXTURE),
                                                              PLAYER_IDLE_FRAMES, 0.2f, true);
    // Construct the primitive GameObject attributes
    position_ = Vector2{100, 100};
    playerData.previousPosition_ = position_;
    dimensions_ = Vector2{PLAYER_LENGTH, PLAYER_LENGTH};
}

#pragma region render methods

// Overridden render methods from the GameObject parent class
void Player::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object

    Texture2D playerTexture = playerData.playerAnimation_->GetTexture();
    Rectangle currentRect = playerData.playerAnimation_->GetCurrentRect();

    playerData.playerAnimation_->FlipX(movingRight_); // flip x axis based on the movingRight_ flag
    // Draw the player utilizing the currently loaded playerTexture, and rect position
    DrawTexturePro(playerTexture, currentRect, GetRect(), Vector2{0, 0}, 0, color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void Player::Update() {
    // Get deltaTime
    float deltaTime = GetFrameTime();
    // State
    StateTransition();
    // Check to see if we need to update the displayed animation
    AnimatePlayer();
    // Reset Jumps
    ResetJumps();
    // Move the player based on their velocity and position
    MovePlayer(deltaTime);
    GameObject::Update();
    playerData.last_state_ = playerData.state_;
}

#pragma endregion

#pragma region movement methods

void Player::MovePlayer(float deltaTime) {
    // Call the updatePosition and velocity changing functions
    ApplyFriction();
    ApplyGravity();
    UpdatePosition(deltaTime);
}

void Player::UpdatePosition(float deltaTime) {
    playerData.previousPosition_ = position_;
    position_.x += velocity_.x * deltaTime;
    position_.y += velocity_.y * deltaTime;
}

void Player::ApplyFriction() {
    const int minVelocity = 50;
    if (velocity_.x > minVelocity) {
        velocity_.x -= FRICTION;
    } else if (velocity_.x < -minVelocity) {
        velocity_.x += FRICTION;
    } else {
        velocity_.x = 0;
    }
}

void Player::ApplyGravity() {
    velocity_.y += GRAVITY;
}

void Player::MoveLeft() {
    // If the player is not also jumping, we'll display the RUNNING animation
    if (velocity_.y == 0 && playerData.state_ != ATTACKING) {
        playerData.state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    movingRight_ = false;
    // Set the player's X velocity
    if (velocity_.x >= -MAX_VELOCITY) {
        velocity_.x -= PLAYER_SPEED;
    }
}

void Player::MoveRight() {
    // If the player is not also jumping, we'll display the RUNNING animation
    if (velocity_.y == 0 && playerData.state_ != ATTACKING) {
        playerData.state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    movingRight_ = true;
    // Set the player's X velocity
    if (velocity_.x <= MAX_VELOCITY) {
        velocity_.x += PLAYER_SPEED;
    }
}

// Make the player jump!
void Player::Jump() {
    // Set isOnGround to false if they jump!
    playerData.isOnGround_ = false;
    // Set jumps and reset player animation
    playerData.jumps_++; // Increment jumps
    playerData.playerAnimation_->Reset(); // Reset the player's animation on Jump (handles double jump animating)
    // Make the player jump!
    const float jumpPower = 6.5f;
    playerData.state_ = JUMPING;
    velocity_.y -= PLAYER_SPEED * jumpPower;
    // Notify of jump event
    Notify(this, EVENT_PLAYER_JUMPED);
}

#pragma endregion

#pragma region player actions

// Make the player attack!
void Player::Attack() {
    // Set the player's state to ATTACKING
    playerData.state_ = ATTACKING;
    Notify(this, EVENT_PLAYER_ATTACK); // Notify relevant observers the player has attacked
}

#pragma endregion

#pragma region player state/animations

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
                TraceLog(LOG_INFO, "Transitioned to IDLE");
                playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_IDLE_TEXTURE), PLAYER_IDLE_FRAMES, idleAnimationSpeed, true);
                break;
            case RUNNING:
                TraceLog(LOG_INFO, "Transitioned to RUNNING");
                playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_RUNNING_TEXTURE), PLAYER_RUNNING_FRAMES, runningAnimationSpeed, true);
                break;
            case JUMPING:
                TraceLog(LOG_INFO, "Transitioned to JUMPING");
                playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_JUMPING_TEXTURE), PLAYER_JUMPING_FRAMES, jumpingAnimationSpeed, false);
                break;
            case ATTACKING:
                TraceLog(LOG_INFO, "Transitioned to ATTACKING");
                playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_ATTACKING_TEXTURE), PLAYER_ATTACKING_FRAMES, playerAttackingSpeed, false);
                break;
        }
    }
}

// Check if the player should go to IDLE state
// This should be called after resetting x or y velocity to 0, and should NOT be called
// after the velocities have been increased to ensure proper state transition
/*
 * Good usage:
 * e.g. PlayerHitFloor (velocity.y set to 0)
 *       call GoIdle, should they be in an Idle state?\
 *
 *
 * Bad usage:
 *
 * Update()
 *      MovePlayer();
 *      ApplyGravity;
 *      GoIdle(); // should not be called here as the velocities have been increased for the frame!
 *
 * This is important, because even if the player is on the ground we apply constant y velocity downwards, so they'd never
 * go idle.
 *
 * We also cannot go IDLE if the player is currently ATTACKING
 */
void Player::StateTransition() {
    if (ZeroVelocity() && (playerData.state_ != ATTACKING)) {
        playerData.state_ = IDLE;
    }
}

bool Player::ZeroVelocity() const {
    return (velocity_.x == 0 && velocity_.y == 0);
}

// Check and return if the player can jump!
bool Player::CanJump() const {
    return playerData.jumps_ <= MAX_JUMPS;
}

// If the player is on the ground, reset their jump counter to 0 and set isOnGround_ to false
// GoIdle() must be called before jumps will be reset, because jumps cannot be reset while JUMPING
void Player::ResetJumps() {
    // If the player's on the ground, reset jumps
    if (playerData.isOnGround_ && playerData.state_ != JUMPING) {
        playerData.jumps_ = 0;
    }
    if (velocity_.y == 0) {
        playerData.isOnGround_ = true;
    }
}

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

// Hit the player externally
void Player::HitPlayer() {
    GameObject::ToggleFlashing();
}

// Return if the player has died
bool Player::CheckPlayerDeath() const {
    return playerData.hp_ <= 0;
}

// Return a ptr to the playerData struct stored in memory
playerDataStruct* Player::GetPlayerData() {
    playerData.timeSinceHit_ = timeSinceToggle_;
    return &playerData;
}

#pragma endregion
