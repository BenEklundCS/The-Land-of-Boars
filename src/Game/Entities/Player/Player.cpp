//
// Created by ben on 5/17/24.
//

#include "../../../../include/Game/Entities/Player/Player.h"

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

    playerData.playerAnimation_->FlipX(playerData.movingRight_); // flip x axis based on the movingRight_ flag
    // Draw the player utilizing the currently loaded playerTexture, and rect position
    DrawTexturePro(playerTexture, currentRect, GetRect(), Vector2{0, 0}, 0, playerData.color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void Player::Update() {
    // Get deltaTime
    float deltaTime = GetFrameTime();
    // State
    // Check to see if we need to update the displayed animation
    AnimatePlayer();
    // Reset Jumps
    ResetJumps();
    // Move the player based on their velocity and position
    MovePlayer(deltaTime);
    playerData.last_state_ = playerData.state_;
    // Update flashing red if hit
    UpdateFlashing(deltaTime);
}

#pragma endregion

#pragma region update methods

void Player::VelocityBound() {
    // If the player's x or y velocity is greater than MAX_VELOCITY,
    if (playerData.velocity_.x > MAX_VELOCITY) playerData.velocity_.x = MAX_VELOCITY;
    if (playerData.velocity_.y > MAX_VELOCITY) playerData.velocity_.y = MAX_VELOCITY;
}

void Player::MovePlayer(float deltaTime) {
    // Call the updatePosition and velocity changing functions
    ApplyFriction();
    ApplyGravity();
    UpdatePosition(deltaTime);
}

void Player::UpdatePosition(float deltaTime) {
    playerData.previousPosition_ = position_;
    position_.x += playerData.velocity_.x * deltaTime;
    position_.y += playerData.velocity_.y * deltaTime;
}

void Player::ApplyFriction() {
    const int minVelocity = 50;
    if (playerData.velocity_.x > minVelocity) {
        playerData.velocity_.x -= FRICTION;
    } else if (playerData.velocity_.x < -minVelocity) {
        playerData.velocity_.x += FRICTION;
    } else {
        playerData.velocity_.x = 0;
    }
}

void Player::ApplyGravity() {
    playerData.velocity_.y += GRAVITY;
}

void Player::MoveLeft() {
    // If the player is not also jumping, we'll display the RUNNING animation
    if (playerData.velocity_.y == 0) {
        playerData.state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    playerData.movingRight_ = false;
    // Set the player's X velocity
    if (playerData.velocity_.x >= -MAX_VELOCITY) {
        playerData.velocity_.x -= PLAYER_SPEED;
    }
}

void Player::MoveRight() {
    // If the player is not also jumping, we'll display the RUNNING animation
    if (playerData.velocity_.y == 0) {
        playerData.state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    playerData.movingRight_ = true;
    // Set the player's X velocity
    if (playerData.velocity_.x <= MAX_VELOCITY) {
        playerData.velocity_.x += PLAYER_SPEED;
    }
}

void Player::Jump() {
    // Set jumps and reset player animation
    playerData.jumps_++; // Increment jumps
    playerData.playerAnimation_->Reset(); // Reset the player's animation on Jump (handles double jump animating)
    // Make the player jump!
    const float jumpPower = 6.5f;
    playerData.state_ = JUMPING;
    playerData.velocity_.y -= PLAYER_SPEED * jumpPower;
}

void Player::AnimatePlayer() {
    // Call Animate to get the next rect
    playerData.playerAnimation_->Animate();

    // Check to see if we need to load a new animation to playerAnimation_
    // We need to load a new animation if state_ != last_state_
    if (playerData.state_ != playerData.last_state_) {

        // Changing state, so get the TextureManager so we can load the next animation
        TextureManager* textureManager = TextureManager::GetInstance();

        // Check to see if we need to load the PLAYER animation
        if (playerData.state_ == IDLE) {
            float idleAnimationSpeed = 0.2f;
            // Invoke the Animation constructor to load a new animation with the IDLE state, and properties
            // replay the idle animation (replay == true)
            playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_IDLE_TEXTURE), PLAYER_IDLE_FRAMES, idleAnimationSpeed, true);
        }

            // Check to see if we need to load the RUNNING animation
        else if (playerData.state_ == RUNNING) {
            float runningAnimationSpeed = 0.2f;
            // Invoke the Animation constructor to load a new animation with the RUNNING state, and properties
            // replay the running animation (replay == true)
            playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_RUNNING_TEXTURE), PLAYER_RUNNING_FRAMES, runningAnimationSpeed, true);
        }

            // Check to see if we need to load the JUMPING animation
        else if (playerData.state_ == JUMPING) {
            float jumpingAnimationSpeed = 0.075f;
            // Invoke the Animation constructor to load a new animation with the JUMPING state, and properties
            // do not replay the jump animation (replay == false)
            playerData.playerAnimation_ = std::make_unique<Animation>(textureManager->GetTexture(PLAYER_JUMPING_TEXTURE), PLAYER_JUMPING_FRAMES, jumpingAnimationSpeed, false);
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
 */
void Player::GoIdle() {
    if (playerData.velocity_.x == 0 && playerData.velocity_.y == 0) {
        playerData.state_ = IDLE;
    }
}

#pragma endregion

#pragma region player state

// Check and return if the player can jump!
bool Player::CanJump() const {
    return (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && playerData.jumps_ <= MAX_JUMPS;
}

// If the player is on the ground, reset their jump counter to 0 and set isOnGround_ to false
// GoIdle() must be called before jumps will be reset, because jumps cannot be reset while JUMPING
void Player::ResetJumps() {
    // If the player's on the ground, reset jumps
    if (playerData.isOnGround_ && playerData.state_ != JUMPING) {
        playerData.jumps_ = 0;
        playerData.isOnGround_ = false; // reset flag after resetting jumps
    }
}

#pragma endregion

#pragma region player object interactions

// Handle a Player Platform collision using bounding rectangles and overlapping axis
void Player::PlatformCollision(GameObject* obj) {
    // Check for collision between the player and the platform
    if (CheckCollisionRecs(GetRect(), obj->GetRect())) {
        // Get the bounding rectangles of the player and the platform
        Rectangle playerRect = this->GetRect();
        Rectangle platformRect = obj->GetRect();

        // Calculate the difference in the x and y positions of the centers of the player and the platform
        float deltaX = (playerRect.x + playerRect.width / 2) - (platformRect.x + platformRect.width / 2);
        float deltaY = (playerRect.y + playerRect.height / 2) - (platformRect.y + platformRect.height / 2);

        // Calculate the combined half-widths and half-heights of the player and the platform
        float combinedHalfWidths = (playerRect.width + platformRect.width) / 2;
        float combinedHalfHeights = (playerRect.height + platformRect.height) / 2;

        // Determine the overlap on both axes
        float overlapX = combinedHalfWidths - std::abs(deltaX);
        float overlapY = combinedHalfHeights - std::abs(deltaY);

        // Revert only the relevant axis position based on the overlap values
        if (overlapX >= overlapY) {
            if (deltaY > 0) { // Collision from above
                position_.y = platformRect.y + platformRect.height;
                // Reset Y velocity only if moving downwards
                if (playerData.velocity_.y < 0) playerData.velocity_.y = 0;
            } else if (deltaY < 0) { // Collision from below
                position_.y = platformRect.y - playerRect.height;
                // Reset Y velocity only if moving upwards
                if (playerData.velocity_.y > 0) playerData.velocity_.y = 0;
                // Set the isOnGround flag and call GoIdle to change state to IDLE
                playerData.isOnGround_ = true;
                GoIdle();
            }
        } else {
            if (deltaX > 0) { // Collision from the left
                position_.x = platformRect.x + platformRect.width;
            } else if (deltaX < 0) { // Collision from the right
                position_.x = platformRect.x - playerRect.width;
            }
        }
    }
}

// Hit the player externally
void Player::HitPlayer() {
    if (!playerData.hasBeenHit_) {
        playerData.hasBeenHit_ = true;
        playerData.timeSinceHit_ = 0.0f;
        playerData.color_ = RED;
    }
}

// Update player flashing behavior
void Player::UpdateFlashing(float deltaTime) {
    playerData.timeSinceHit_ += deltaTime;
    playerData.timeStepForFlash_ += deltaTime;

    if (playerData.hasBeenHit_) {

        if (playerData.timeStepForFlash_ > 0.2f) {
            playerData.flashToggle_ = !(bool)playerData.flashToggle_;
            if (playerData.flashToggle_ == false) {
                playerData.color_ = RED;
            } else {
                playerData.color_ = WHITE;
            }
            playerData.timeStepForFlash_ = 0.0f;
        }

        if (playerData.timeSinceHit_ > 1.0f) {
            playerData.hasBeenHit_ = false;
            playerData.color_ = WHITE;
        }
    }
}

// Return if the player has died
bool Player::CheckPlayerDeath() const {
    return playerData.hp_ <= 0;
}

// Return a ptr to the playerData struct stored in memory
playerDataStruct* Player::GetPlayerData() {
    return &playerData;
}

#pragma endregion
