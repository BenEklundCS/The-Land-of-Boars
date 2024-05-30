//
// Created by ben on 5/17/24.
//

#include "Player.h"
#include "../../../../Platform/include/Scene.h"

Player::Player() : playerAnimation_(TextureManager::GetInstance()->GetTexture(PLAYER_IDLE_TEXTURE),
                                                   PLAYER_IDLE_FRAMES, 0.2f, true), GameObject(PLAYER) {
    this->position_ = {100, 100};
    this->dimensions_ = {PLAYER_LENGTH, PLAYER_LENGTH};
    this->state_ = IDLE;
    this->last_state_ = IDLE;
    this->movingRight_ = true;
}

void Player::Draw() {
    // Get the playerTexture sheet and currentRect from the Animation object
    Texture2D playerTexture = playerAnimation_.GetTexture();
    Rectangle currentRect = playerAnimation_.GetCurrentRect();
    playerAnimation_.FlipX(movingRight_); // flip x axis based on the movingRight_ flag
    // Draw the player utilizing the currently loaded playerTexture, and rect position
    DrawTexturePro(playerTexture, currentRect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

// ORDER MATTERS IN THIS METHOD, BEWARE
void Player::Update() {
    float deltaTime = GetFrameTime();
    // Update state information FIRST
    last_state_ = state_;
    if (velocity_.x == 0 && velocity_.y == 0) {
        state_ = IDLE;
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
}

void Player::VelocityBound() {
    if (velocity_.x > MAX_VELOCITY) velocity_.x = MAX_VELOCITY;
    if (velocity_.y > MAX_VELOCITY) velocity_.y = MAX_VELOCITY;
}

void Player::ResetJumps() {
    if (velocity_.y == 0) {
        jumps_ = 0;
    }
}

void Player::MovePlayer(float deltaTime) {
    ApplyFriction(deltaTime);
    ApplyGravity(deltaTime);
    UpdatePosition();
}

void Player::UpdatePosition() {
    position_.x += velocity_.x;
    position_.y += velocity_.y;
}

void Player::ApplyFriction(float deltaTime) {
    const int minVelocity = 1;
    if (velocity_.x > minVelocity) {
        velocity_.x -= FRICTION * deltaTime;
    } else if (velocity_.x < -minVelocity) {
        velocity_.x += FRICTION * deltaTime;
    } else {
        velocity_.x = 0;
    }
}

void Player::ApplyGravity(float deltaTime) {
    velocity_.y += GRAVITY * deltaTime;
}

void Player::MoveLeft(float deltaTime) {
    float maxXVelocity = 25;
    // If the player is not also jumping, we'll display the RUNNING animation
    if (velocity_.y == 0) {
        state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    movingRight_ = false;
    // Set the player's X velocity
    if (velocity_.x >= -maxXVelocity) {
        velocity_.x -= PLAYER_SPEED * deltaTime;
    }
}

void Player::MoveRight(float deltaTime) {
    float maxXVelocity = 25;
    // If the player is not also jumping, we'll display the RUNNING animation
    if (velocity_.y == 0) {
        state_ = RUNNING;
    }
    // Flip the animation across the X axis - feed the "moving right" boolean value
    movingRight_ = true;
    // Set the player's X velocity
    if (velocity_.x <= maxXVelocity) {
        velocity_.x += PLAYER_SPEED * deltaTime;
    }
}

void Player::Jump(float deltaTime) {
    const float jumpPower = 6.5f;
    state_ = JUMPING;
    velocity_.y -= PLAYER_SPEED * jumpPower * deltaTime;
}

void Player::HandlePlayerInput(float deltaTime) {
    if (IsKeyDown(KEY_LEFT)) { // move left
        MoveLeft(deltaTime);
    }
    if (IsKeyDown(KEY_RIGHT)) { // move right
        MoveRight(deltaTime);
    }
    // Handle jumping and jump animation state management
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && jumps_ <= MAX_JUMPS) { // jump
        jumps_++;
        Jump(deltaTime);
    }
    if (IsKeyPressed(KEY_N)) {
        Scene::SetLevelOver();
    }
}

void Player::PlatformCollision(GameObject* obj) {
    if (CheckCollisionRecs(GetRect(), obj->GetRect())) {
        Rectangle playerRect = GetRect();
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
                velocity_.y = 0;
                // Reset jumps on collision from above
            } else { // Collision from below
                position_.y = platformRect.y - playerRect.height;
                velocity_.y = 0;
            }
        } else {
            if (deltaX > 0) { // Collision from the left
                position_.x = platformRect.x + platformRect.width;
                velocity_.x = 0;
            } else { // Collision from the right
                position_.x = platformRect.x - playerRect.width;
                velocity_.x = 0;
            }
        }
    }
}

void Player::HitPlayer() {
    hp_--;
}

bool Player::CheckPlayerDeath() const {
    return hp_ <= 0;
}

void Player::AnimatePlayer() {
    // Call Animate to get the next rect
    playerAnimation_.Animate();
    // Check to see if we need to load the IDLE animation
    if (state_ != last_state_) {
        // Changing state, so get the TextureManager
        TextureManager* textureManager = TextureManager::GetInstance();
        // Check to see if we need to load the PLAYER animation
        if (state_ == IDLE && last_state_ != IDLE) { // replay the idle animation (replay == true)
            float idleAnimationSpeed = 0.2f;
            playerAnimation_ = Animation(textureManager->GetTexture(PLAYER_IDLE_TEXTURE), PLAYER_IDLE_FRAMES, idleAnimationSpeed, true);
        }
            // Check to see if we need to load the RUNNING animation
        else if (state_ == RUNNING && last_state_ != RUNNING) { // replay the running animation (replay == true)
            float runningAnimationSpeed = 0.2f;
            playerAnimation_ = Animation(textureManager->GetTexture(PLAYER_RUNNING_TEXTURE), PLAYER_RUNNING_FRAMES, runningAnimationSpeed, true);
        }
            // Check to see if we need to load the JUMPING animation
        else if (state_ == JUMPING && last_state_ != JUMPING) { // do not replay the jump animation (replay == false)
            float jumpingAnimationSpeed = 0.075f;
            playerAnimation_ = Animation(textureManager->GetTexture(PLAYER_JUMPING_TEXTURE), PLAYER_JUMPING_FRAMES, jumpingAnimationSpeed, false);
        }
    }
}

