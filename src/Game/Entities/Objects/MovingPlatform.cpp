//
// Created by ben on 7/15/24.
//

#include "../../../../include/Game/Entities/Objects/MovingPlatform.h"
#include "raylib.h"

// Constructor for MovingPlatform, initializing the base Platform class using an existing Platform object
MovingPlatform::MovingPlatform(std::unique_ptr<Platform> platform, Vector2 boundsX, Vector2 boundsY, float speed, bool LR, bool UD)
        : Platform(*platform), boundsX(boundsX), boundsY(boundsY),
          moveLeftRight(LR), moveUpDown(UD),
          startingXY(Vector2{platform->GetPosition().x, platform->GetPosition().y}) {
    speed_ = speed;
    position_ = platform->GetPosition();
    type_ = MOVING_PLATFORM;
}

#pragma region main methods

// Update call for the MovingPlatform
void MovingPlatform::Update() {
    float deltaTime = GetFrameTime();
    if (moveLeftRight) {
        MoveLeftRight(deltaTime);
    }
    if (moveUpDown) {
        MoveUpDown(deltaTime);
    }
    SwapDirection();
}

// Draw the MovingPlatform
void MovingPlatform::Draw() {
    DrawRectangleRec(GetRect(), color_);
}

#pragma endregion

#pragma region movement

// Move the platform left/right if that flag is set
void MovingPlatform::MoveLeftRight(float deltaTime) {
    if (movingRight) {
        position_.x += speed_ * deltaTime;
    }
    else {
        position_.x -= speed_ * deltaTime;
    }
}

// Move the platform up/down if that flag is set
void MovingPlatform::MoveUpDown(float deltaTime) {
    if (movingUp) {
        position_.y += speed_ * deltaTime;
    }
    else {
        position_.y -= speed_ * deltaTime;
    }
}

#pragma endregion

#pragma region collisions/swapping

// This method swaps the MovingPlatform's X direction if it hits the left or right boundary
// and swaps the Y direction if it hits the top of bottom boundary
void MovingPlatform::SwapDirection() {
    // Swap right/left direction if it reaches the edge of the boundary on either side
    if (HitLeftBound() || HitRightBound()) {
        movingRight = !movingRight;
    }
    // Swap up/down direction if it reaches the edge of the boundary on either side
    if ((HitBottomBound()|| HitTopBound())) {
        movingUp = !movingUp;
    }
}

/*
 * |------|
 * | *    |
 * |------|
 */
// returns true if the platform has reached the left boundary
bool MovingPlatform::HitLeftBound() {
    return (!movingRight && position_.x <= startingXY.x + boundsX.x);
}

/*
 * |------|
 * |    * |
 * |------|
 */
// returns true if the platform has reached the right boundary
bool MovingPlatform::HitRightBound() {
    return (movingRight && position_.x >= startingXY.x + dimensions_.x + boundsX.y);
}

/*
 * |- *  -|
 * |      |
 * |------|
 */
// returns true if the platform has reached the top boundary
bool MovingPlatform::HitTopBound() {
    return (!movingUp && position_.y <= startingXY.y + boundsY.x);
}

/*
 * |------|
 * |      |
 * |-  * -|
 */
// returns true if the platform has reached the bottom boundary
bool MovingPlatform::HitBottomBound() {
    return (movingUp && position_.y >= startingXY.y + dimensions_.y + boundsY.y);
}

float MovingPlatform::GetSpeed() {
    return speed_;
}

#pragma endregion


