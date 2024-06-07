//
// Created by ben on 5/17/24.
//

#include "../../../../include/Game/Entities/Player/Player.h"

Player::Player() : GameObject(PLAYER){
    // Load it here to ensure the TextureManager is queried after the player object is created
    playerData.playerAnimation_ = std::make_unique<Animation>(TextureManager::GetInstance()->GetTexture(PLAYER_IDLE_TEXTURE),
                                PLAYER_IDLE_FRAMES, 0.2f, true);
    // Construct the primitize GameObject attributes
    position_ = Vector2{100, 100};
    dimensions_ = Vector2{PLAYER_LENGTH, PLAYER_LENGTH};
}

#pragma region render methods

// Overridden render methods from the GameObject parent class

// Draw the player to the screen. Uses the playerAnimation_ member to determine which rect to draw
// From the playerTexture. Flips the player across the X axis depending on the movingRight_ boolean.
void Player::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object

    Texture2D playerTexture = playerData.playerAnimation_->GetTexture();
    Rectangle currentRect = playerData.playerAnimation_->GetCurrentRect();

    playerData.playerAnimation_->FlipX(playerData.movingRight_); // flip x axis based on the movingRight_ flag
    // Draw the player utilizing the currently loaded playerTexture, and rect position
    DrawTexturePro(playerTexture, currentRect, GetRect(), Vector2{0, 0}, 0, playerData.color_);     // Draw a part of a texture defined by a rectangle with 'pro' parameters

    // Debug
    //DrawRectangle(position_.x, position_.y, GetRect().width, GetRect().height, RED);
}

// Update the player for the frame
// Get the frame time and then
void Player::Update() {
    float deltaTime = GetFrameTime();
    // Update state information FIRST
    playerData.last_state_ = playerData.state_;
    if (playerData.velocity_.x == 0 && playerData.velocity_.y == 0) {
        playerData.state_ = IDLE;
    }
    // Reset Jumps
    ResetJumps();
    // Handle Player Input
    HandlePlayerInput(deltaTime);
    // Stop crazy acceleration
    VelocityBound();
    // Move the player based on their velocity and position
    MovePlayer(deltaTime);
    // Check to see if we need to update the displayed animation
    AnimatePlayer();
    // Update flashing red if hit
    UpdateFlashing(deltaTime);
}

#pragma endregion

#pragma region update methods

void Player::VelocityBound() {
    // If the players x or y velocity is greater than MAX_VELOCITY,
    if (playerData.velocity_.x > MAX_VELOCITY) playerData.velocity_.x = MAX_VELOCITY;
    if (playerData.velocity_.y > MAX_VELOCITY) playerData.velocity_.y = MAX_VELOCITY;
}

void Player::MovePlayer(float deltaTime) {
    // Call the updatePosition and velocity changing functions
    ApplyFriction(deltaTime);
    ApplyGravity(deltaTime);
    UpdatePosition();
}

void Player::UpdatePosition() {
    position_.x += playerData.velocity_.x;
    position_.y += playerData.velocity_.y;
}

void Player::ApplyFriction(float deltaTime) {
    const int minVelocity = 1;
    if (playerData.velocity_.x > minVelocity) {
        playerData.velocity_.x -= FRICTION * deltaTime;
    } else if (playerData.velocity_.x < -minVelocity) {
        playerData.velocity_.x += FRICTION * deltaTime;
    } else {
        playerData.velocity_.x = 0;
    }
}

void Player::ApplyGravity(float deltaTime) {
    playerData.velocity_.y += GRAVITY * deltaTime;
}

void Player::MoveLeft(float deltaTime) {
    float maxXVelocity = 25;
    // If the player is not also jumping, we'll display the RUNNING animation
    if (playerData.velocity_.y == 0) {
        playerData.state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    playerData.movingRight_ = false;
    // Set the player's X velocity
    if (playerData.velocity_.x >= -maxXVelocity) {
        playerData.velocity_.x -= PLAYER_SPEED * deltaTime;
    }
}

void Player::MoveRight(float deltaTime) {
    float maxXVelocity = 25;
    // If the player is not also jumping, we'll display the RUNNING animation
    if (playerData.velocity_.y == 0) {
        playerData.state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    playerData.movingRight_ = true;
    // Set the player's X velocity
    if (playerData.velocity_.x <= maxXVelocity) {
        playerData.velocity_.x += PLAYER_SPEED * deltaTime;
    }
}

void Player::Jump(float deltaTime) {
    // Set jumps and reset player animation
    playerData.jumps_++; // Increment jumps
    playerData.playerAnimation_->Reset(); // Reset the player's animation on Jump (handles double jump animating)
    // Make the player jump!
    const float jumpPower = 6.5f;
    playerData.state_ = JUMPING;
    playerData.velocity_.y -= PLAYER_SPEED * jumpPower * deltaTime;
}

void Player::HandlePlayerInput(float deltaTime) {
    if (IsKeyDown(KEY_LEFT)) MoveLeft(deltaTime); // move left on left keypress
    if (IsKeyDown(KEY_RIGHT)) MoveRight(deltaTime); // move right on right keypress

    // Handle jumping and jump animation state management
    if (CanJump()) { // jump
        Jump(deltaTime); // Call jump to make the player jump
    }
}

// Animate the player by calling .Animate on the playerAnimation_
// If the state_ is not equal to the last_state_, then we need to load the next playerAnimation for rendering
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

#pragma endregion

#pragma region player state

bool Player::CanJump() const {
    return (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && playerData.jumps_ <= MAX_JUMPS;
}

void Player::ResetJumps() {
    // If the player's y velocity is 0, they're allowed to jump again
    if (playerData.velocity_.y == 0) {
        playerData.jumps_ = 0;
    }
}

#pragma endregion

#pragma region player object interactions

// Respond to a platform collision, adjusting the players position and velocity
// Invoke this method when the player should interact with the passed GameObject as if it is a solid block/platform/tile
void Player::PlatformCollision(GameObject* obj) {
    // Check to see if the objects have collided
    if (CheckCollisionRecs(GetRect(), obj->GetRect())) {
        // If so, we do some crazy math to handle the collision with the Platform
        Rectangle playerRect = this->GetRect();
        Rectangle platformRect = obj->GetRect();

        float deltaX = (playerRect.x + playerRect.width / 2) - (platformRect.x + platformRect.width / 2);
        float deltaY = (playerRect.y + playerRect.height / 2) - (platformRect.y + platformRect.height / 2);

        float combinedHalfWidths = (playerRect.width + platformRect.width) / 2;
        float combinedHalfHeights = (playerRect.height + platformRect.height) / 2;

        // Determine the overlap on both axes
        float overlapX = combinedHalfWidths - std::abs(deltaX);
        float overlapY = combinedHalfHeights - std::abs(deltaY);

        if (overlapX >= overlapY) {
            if (deltaY > 0) { // Collision from above
                position_.y = platformRect.y + platformRect.height;
                playerData.velocity_.y = 0;
                // Reset jumps on collision from above
            } else { // Collision from below
                position_.y = platformRect.y - playerRect.height;
                playerData.velocity_.y = 0;
            }
        } else {
            if (deltaX > 0) { // Collision from the left
                position_.x = platformRect.x + platformRect.width;
                playerData.velocity_.x = 0;
            } else { // Collision from the right
                position_.x = platformRect.x - playerRect.width;
                playerData.velocity_.x = 0;
            }
        }
    }
}

void Player::HitPlayer() {
    if (!playerData.hasBeenHit_) {
        playerData.hasBeenHit_ = true;
        playerData.timeSinceHit_ = 0.0f;
        playerData.color_ = RED;
    }
}

void Player::UpdateFlashing(float deltaTime) {
    playerData.timeSinceHit_ += deltaTime;
    playerData.timeStepForFlash_ += deltaTime;

    if (playerData.hasBeenHit_) {

        if (playerData.timeStepForFlash_ > 0.2f) {
            playerData.flashToggle_ = !(bool)playerData.flashToggle_;
            if (playerData.flashToggle_ == false) {
                playerData.color_ = RED;
            }
            else {
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

bool Player::CheckPlayerDeath() const {
    return playerData.hp_ <= 0;
}

playerDataStruct* Player::GetPlayerData() {
    return &playerData;
}

#pragma endregion

