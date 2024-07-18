//
// Created by ben on 7/15/24.
//

#include "../../../../include/Game/Entities/Objects/MovingPlatform.h"
#include "raylib.h"

// Constructor for MovingPlatform, initializing the base Platform class using an existing Platform object
MovingPlatform::MovingPlatform(std::unique_ptr<Platform> platform, Vector2 boundsX, Vector2 boundsY, bool LR, bool UD)
        : Platform(*platform), boundsX(boundsX), boundsY(boundsY),
          moveLeftRight(LR), moveUpDown(UD),
          startingXY(Vector2{platform->GetPosition().x, platform->GetPosition().y}) {
    position_ = platform->GetPosition();
}

void MovingPlatform::Update() {
    float deltaTime = GetFrameTime();
    if (moveLeftRight) {
        // Swap if at edge
        if ((!movingRight && position_.x <= startingXY.x + boundsX.x) || (movingRight && position_.x >= startingXY.x + dimensions_.x + boundsX.y)) {
            movingRight = !movingRight;
        }
        if (movingRight) {
            position_.x += 100 * deltaTime;
        }
        else {
            position_.x -= 100 * deltaTime;
        }
    }
    if (moveUpDown) {
        if ((!movingUp && position_.y <= startingXY.y + boundsY.x) || (movingUp && position_.y >= startingXY.y + dimensions_.y + boundsY.y) ) {
            movingUp = !movingUp;
        }
        if (movingUp) {
            position_.y += 100 * deltaTime;
        }
        else {
            position_.y -= 100 * deltaTime;
        }
    }
}

void MovingPlatform::Draw() {
    DrawRectangleRec(GetRect(), color_);
}
