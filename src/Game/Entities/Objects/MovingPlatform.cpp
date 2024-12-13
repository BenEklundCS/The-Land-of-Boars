//
// Created by ben on 7/15/24.
//

#include "../../../../include/Game/Entities/Objects/MovingPlatform.h"
#include "raylib.h"

/**
 * @brief Constructs a MovingPlatform object.
 *
 * Initializes a MovingPlatform using an existing Platform object. The movement is configured
 * with speed, boundaries, and flags indicating whether the platform moves horizontally or vertically.
 *
 * @param platform A unique pointer to the base Platform object to initialize from.
 * @param boundsX Horizontal movement boundaries (X-axis range relative to the starting position).
 * @param boundsY Vertical movement boundaries (Y-axis range relative to the starting position).
 * @param speed The speed at which the platform moves.
 * @param LR Flag indicating if the platform moves left/right.
 * @param UD Flag indicating if the platform moves up/down.
 */
MovingPlatform::MovingPlatform(const std::unique_ptr<Platform> &platform, const Vector2 boundsX, const Vector2 boundsY, const float speed, const bool LR, const bool UD)
        : Platform(*platform), boundsX(boundsX), boundsY(boundsY),
          moveLeftRight(LR), moveUpDown(UD),
          startingXY(Vector2{platform->GetPosition().x, platform->GetPosition().y}) {
    speed_ = speed;
    position_ = platform->GetPosition();
    type_ = MOVING_PLATFORM;
}

#pragma region main methods

/**
 * @brief Updates the MovingPlatform's position based on its movement flags and speed.
 *
 * The platform moves left/right or up/down depending on the configuration, and the direction is swapped
 * when the platform reaches its movement boundaries.
 */
void MovingPlatform::Update() {
    const float deltaTime = GetFrameTime();
    if (moveLeftRight) {
        MoveLeftRight(deltaTime);
    }
    if (moveUpDown) {
        MoveUpDown(deltaTime);
    }
    SwapDirection();
}

/**
 * @brief Draws the MovingPlatform as a rectangle.
 *
 * Uses the Raylib `DrawRectangleRec` function for rendering.
 */
void MovingPlatform::Draw() {
    DrawRectangleRec(GetRect(), color_);
}

#pragma endregion

#pragma region movement

/**
 * @brief Moves the platform left or right based on the current direction.
 *
 * @param deltaTime The time elapsed since the last frame.
 */
void MovingPlatform::MoveLeftRight(const float deltaTime) {
    if (movingRight) {
        position_.x += speed_ * deltaTime;
    }
    else {
        position_.x -= speed_ * deltaTime;
    }
}

/**
 * @brief Moves the platform up or down based on the current direction.
 *
 * @param deltaTime The time elapsed since the last frame.
 */
void MovingPlatform::MoveUpDown(const float deltaTime) {
    if (movingUp) {
        position_.y += speed_ * deltaTime;
    }
    else {
        position_.y -= speed_ * deltaTime;
    }
}

#pragma endregion

#pragma region collisions/swapping

/**
 * @brief Swaps the platform's direction when it reaches the boundaries of its movement range.
 */
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
/**
 * @brief Checks if the platform has reached the left boundary.
 *
 * @return True if the platform has hit the left boundary, false otherwise.
 */
bool MovingPlatform::HitLeftBound() const {
    return (!movingRight && position_.x <= startingXY.x + boundsX.x);
}

/*
 * |------|
 * |    * |
 * |------|
 */
/**
 * @brief Checks if the platform has reached the right boundary.
 *
 * @return True if the platform has hit the right boundary, false otherwise.
 */
bool MovingPlatform::HitRightBound() const {
    return (movingRight && position_.x >= startingXY.x + dimensions_.x + boundsX.y);
}

/*
 * |- *  -|
 * |      |
 * |------|
 */
/**
 * @brief Checks if the platform has reached the top boundary.
 *
 * @return True if the platform has hit the top boundary, false otherwise.
 */
bool MovingPlatform::HitTopBound() const {
    return (!movingUp && position_.y <= startingXY.y + boundsY.x);
}

/*
 * |------|
 * |      |
 * |-  * -|
 */
/**
 * @brief Checks if the platform has reached the bottom boundary.
 *
 * @return True if the platform has hit the bottom boundary, false otherwise.
 */
bool MovingPlatform::HitBottomBound() const {
    return (movingUp && position_.y >= startingXY.y + dimensions_.y + boundsY.y);
}

/**
 * @brief Retrieves the speed of the MovingPlatform.
 *
 * @return The current speed of the platform.
 */
float MovingPlatform::GetSpeed() const {
    return speed_;
}

/**
 * @brief Retrieves the platform's movement vector.
 *
 * @return A Vector2 representing the movement direction and speed of the platform.
 */
Vector2 MovingPlatform::GetMovement() const {
    return Vector2{speed_ * static_cast<float>(movingRight ? 1 : -1), speed_ * static_cast<float>(movingUp ? 1 : -1)};
}

#pragma endregion


