//
// Created by ben on 5/17/24.
//

#include "Player.h"
#include "../Sprites/TextureManager.h"

Player::Player() : playerAnimation_(TextureManager::GetTexture("playerIdleTexture"), PLAYER_IDLE_FRAMES, 0.2f) {
    this->position_ = {100, 100};
    this->dimensions_ = {PLAYER_LENGTH, PLAYER_LENGTH};
    this->color_ = BLUE;
    last_state = IDLE;
}

void Player::Draw() {
    Texture2D playerTexture = playerAnimation_.GetTexture();
    Rectangle currentRect = playerAnimation_.GetCurrentRect();
    DrawTexturePro(playerTexture, currentRect, GetRect(), Vector2{0, 0}, 0, WHITE);     // Draw a part of a texture defined by a rectangle with 'pro' parameters
    last_state = state;
}

void Player::Update() {
    // Handle Player Input
    HandlePlayerInput();
    if (velocity_.x == 0 && state != JUMPING) {  // Check if the player is not moving and not in the air
        state = IDLE;
    }
    MovePlayer();
    AnimatePlayer();
    playerAnimation_.Animate();
}

void Player::MovePlayer() {

    float deltaTime = GetFrameTime();
    const int minVelocity = 1;

    // X axis movement
    position_.x += velocity_.x; // Update the X position based on the X-axis velocity

    // Handle friction / velocity reduction over time
    if (velocity_.x > minVelocity) {
        velocity_.x -= FRICTION * deltaTime; // friction
    }
    else if (velocity_.x < -minVelocity) {
        velocity_.x += FRICTION * deltaTime; // friction
    }
    else {
        velocity_.x = 0;
    }

    // Gravity
    velocity_.y += GRAVITY * deltaTime;
    // Apply vertical velocity
    position_.y += velocity_.y;
}

void Player::HandlePlayerInput() {

    float deltaTime = GetFrameTime();

    float maxXVelocity = 25;

    const float jumpPower = 7;

    if (IsKeyDown(KEY_A)) { // move left
        state = RUNNING;
        playerAnimation_.FlipX(false); // flip x, not moving right
        if (velocity_.x >= -maxXVelocity) {
            velocity_.x -= PLAYER_SPEED * deltaTime;
        }
    }
    if (IsKeyDown(KEY_D)) { // move right
        state = RUNNING;
        playerAnimation_.FlipX(true); // flip x, moving right
        if (velocity_.x <= maxXVelocity) {
            velocity_.x += PLAYER_SPEED * deltaTime;
        }
    }
    if ((IsKeyPressed(KEY_SPACE) && velocity_.y == 0)) { // jump
        state = JUMPING;
        velocity_.y -= PLAYER_SPEED * jumpPower * deltaTime;
    }
}

void Player::PlatformCollision(GameObject* obj) {
    // Stop the player's downward movement
    velocity_ = Vector2{velocity_.x, 0};
    // Set the player's position to be just above the object
    position_ = Vector2{position_.x, obj->GetPosition().y - dimensions_.y};
}

void Player::AnimatePlayer() {
    if (state == IDLE && last_state != IDLE) {
        TraceLog(LOG_INFO, "IDLE");
        playerAnimation_ = Animation(TextureManager::GetTexture(PLAYER_IDLE_TEXTURE), PLAYER_IDLE_FRAMES, 0.2f);
    }
    else if (state == RUNNING && last_state != RUNNING) {
        TraceLog(LOG_INFO, "RUNNING");
        playerAnimation_ = Animation(TextureManager::GetTexture(PLAYER_RUNNING_TEXTURE), PLAYER_RUNNING_FRAMES, 0.2f);
    }

}

