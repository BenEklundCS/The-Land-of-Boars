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
}

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

// Move the platform left/right if that flag is set
void MovingPlatform::MoveLeftRight(float deltaTime) {
    if (movingRight) {
        position_.x += 100 * deltaTime;
    }
    else {
        position_.x -= 100 * deltaTime;
    }
}

// Move the platform up/down if that flag is set
void MovingPlatform::MoveUpDown(float deltaTime) {
    if (movingUp) {
        position_.y += 100 * deltaTime;
    }
    else {
        position_.y -= 100 * deltaTime;
    }
}

// This method swaps the MovingPlatform's X direction if it hits the left or right boundary
// and swaps the Y direction if it hits the top of bottom boundary
void MovingPlatform::SwapDirection() {
    // Swap right/left direction if it reaches the edge of the boundary on either side
    if ((!movingRight && position_.x <= startingXY.x + boundsX.x) || (movingRight && position_.x >= startingXY.x + dimensions_.x + boundsX.y)) {
        movingRight = !movingRight;
    }
    // Swap up/down direction if it reaches the edge of the boundary on either side
    if ((!movingUp && position_.y <= startingXY.y + boundsY.x) || (movingUp && position_.y >= startingXY.y + dimensions_.y + boundsY.y) ) {
        movingUp = !movingUp;
    }
}
