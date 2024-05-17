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
    HandlePlayerInput(&position_);

    // Gravity
    if (position_.y < (float)(GetScreenHeight() - PLAYER_LENGTH * 2)) {
        position_.y += 10;
    }
}

void Player::SetPosition(Vector2 position) {
    this->position_ = position;
}

Vector2 Player::GetPosition() {
    return position_;
}

Vector2 Player::GetDimensions() {
    return dimensions_;
}

Color Player::GetColor() {
    return this->color_;
}
