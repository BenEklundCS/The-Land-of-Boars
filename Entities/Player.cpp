//
// Created by ben on 5/17/24.
//

#include "Player.h"
#include "../Renderer/TextureManager.h"

Player::Player() {
    this->position_ = {100, 100};
    this->dimensions_ = {PLAYER_LENGTH, PLAYER_LENGTH};
    this->color_ = BLUE;
}

void Player::Draw() {
    DrawTexturePro(TextureManager::GetTexture("playerTexture"), TextureManager::GetRect("playerRect"), GetRect(), Vector2{0, 0}, 0, WHITE);
    // RLAPI void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);           // Draw a part of a texture defined by a rectangle with 'pro' parameters
}

void Player::Update() {
    // Handle Player Input
    HandlePlayerInput();
    MovePlayer();
}

Color Player::GetColor() {
    return this->color_;
}

void Player::MovePlayer() {
    float deltaTime = GetFrameTime();
    // X axis movement
    position_.x += velocity_.x;
    if (velocity_.x > MIN_VELOCITY) {
        velocity_.x -= FRICTION * deltaTime; // friction
    }
    else if (velocity_.x < -MIN_VELOCITY) {
        velocity_.x += FRICTION * deltaTime; // friction
    }
    else {
        velocity_.x = 0;
    }

    // Gravity

    velocity_.y += GRAVITY * deltaTime;

    // Apply vertical velocity
    position_.y += velocity_.y;

    // Stop the player from falling through the floor
    if (position_.y > (float)(GetScreenHeight())) {
        position_.y = (float)(GetScreenHeight());
        velocity_.y = 0;
    }
}

void Player::HandlePlayerInput() {

    float deltaTime = GetFrameTime();

    float maxXVelocity = 25;

    if (IsKeyDown(KEY_A)) { // move left
        if (playerTextureRect.width > 0) {
            playerTextureRect.width *= -1;
        }
        if (velocity_.x >= -maxXVelocity) {
            velocity_.x -= PLAYER_SPEED * deltaTime;
        }
    }
    if (IsKeyDown(KEY_D)) { // move right
        if (playerTextureRect.width < 0) {
            playerTextureRect.width *= -1;
        }
        if (velocity_.x <= maxXVelocity) {
            velocity_.x += PLAYER_SPEED * deltaTime;
        }
    }
    if ((IsKeyPressed(KEY_SPACE) && velocity_.y == 0)) { // jump
        velocity_.y -= PLAYER_SPEED * JUMP_POWER * deltaTime;
    }
}

Vector2 Player::GetVelocity() {
    return velocity_;
}

void Player::SetVelocity(Vector2 velocity) {
    this->velocity_ = velocity;
}

