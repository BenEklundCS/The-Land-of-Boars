//
// Created by ben on 5/17/24.
//

#include "Player.h"

Player::Player() {
    this->position_ = {100, 100};
    this->dimensions_ = {100, 100};
    this->color_ = RED;
}

void Player::Draw() {
    DrawRectangle((int)GetPosition().x, (int)GetPosition().y,
                  (int)GetDimensions().x, (int)GetDimensions().y,
                  GetColor());
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
    // X axis movement
    position_.x += velocity_.x;
    if (velocity_.x > 0) {
        velocity_.x -= 3; // friction
    }
    else if (velocity_.x < 0) {
        velocity_.x += 3; // friction
    }
    else {
        velocity_.x = 0;
    }

    // Gravity
    float deltaTime = GetFrameTime();
    velocity_.y += GRAVITY * deltaTime;

    // Apply vertical velocity
    position_.y += velocity_.y;

    // Stop the player from falling through the floor
    if (position_.y > (float)(GetScreenHeight() - PLAYER_LENGTH * 2)) {
        position_.y = (float)(GetScreenHeight() - PLAYER_LENGTH * 2);
        velocity_.y = 0;
    }
}

void Player::HandlePlayerInput() {
    float maxXVelocity = 25;

    if (IsKeyDown(KEY_A)) { // move left
        if (velocity_.x >= -maxXVelocity) {
            velocity_.x -= 15;
        }
    }
    if (IsKeyDown(KEY_D)) { // move right
        if (velocity_.x <= maxXVelocity) {
            velocity_.x += 15;
        }
    }
    if ((IsKeyPressed(KEY_SPACE) && velocity_.y == 0)) { // jump
        velocity_.y -= 30;
    }
}
