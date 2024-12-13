//
// Created by ben on 7/15/24.
//

#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

#include "Platform.h"

/**
 * @file MovingPlatform.h
 * @brief Defines the MovingPlatform class, which represents a platform that moves along specified boundaries.
 *
 * This class extends the Platform class and adds functionality for a platform to move along defined boundaries,
 * either horizontally or vertically. It provides methods for updating movement, handling collisions, and drawing the platform.
 */

/**
 * @class MovingPlatform
 * @brief Represents a platform that moves along specified boundaries in the game.
 *
 * The MovingPlatform class inherits from the Platform class and allows for the movement of platforms
 * within specified horizontal and vertical bounds. The platform can move left-right or up-down and includes
 * collision detection to prevent it from moving beyond its boundaries.
 */
class MovingPlatform : public Platform {
public:
    /**
     * @brief Constructs a MovingPlatform with a specified platform, movement bounds, and speed.
     *
     * Initializes the platform's starting position, boundaries, movement behavior, and speed.
     *
     * @param platform A unique pointer to the platform to be moved.
     * @param boundsX The horizontal movement boundaries.
     * @param boundsY The vertical movement boundaries.
     * @param speed The speed at which the platform moves.
     * @param LR A flag indicating if the platform should move left-right.
     * @param UD A flag indicating if the platform should move up-down.
     */
    MovingPlatform(const std::unique_ptr<Platform> &platform, Vector2 boundsX, Vector2 boundsY, float speed, bool LR, bool UD);

    /**
     * @brief Updates the movement and position of the platform.
     *
     * This method overrides the base class's Update method and moves the platform within its bounds.
     */
    void Update() override;

    /**
     * @brief Returns the speed at which the platform moves.
     *
     * @return The movement speed of the platform.
     */
    float GetSpeed() const;

private:
    // **Position and Boundaries**
    Vector2 startingXY; ///< The starting position of the platform.
    Vector2 boundsX; ///< The horizontal movement boundaries.
    Vector2 boundsY; ///< The vertical movement boundaries.

    // **Movement Behavior Flags**
    bool moveLeftRight; ///< Indicates whether the platform moves left-right.
    bool moveUpDown; ///< Indicates whether the platform moves up-down.

    // **Current Movement Direction Flags**
    bool movingRight = true; ///< Current direction flag for left-right movement.
    bool movingUp = true; ///< Current direction flag for up-down movement.

    // **Desired Movement Speed**
    float speed_; ///< The speed at which the platform moves.

    // **Private Movement Methods**
    void MoveLeftRight(float deltaTime); ///< Moves the platform left or right based on deltaTime.
    void MoveUpDown(float deltaTime); ///< Moves the platform up or down based on deltaTime.
    void SwapDirection(); ///< Swaps the direction of movement when a boundary is hit.

    /**
     * @brief Draws the moving platform on the screen.
     *
     * This method overrides the base class's Draw method to render the platform at its current position.
     */
    void Draw() override;

    // **Collision Detection Methods**
    bool HitLeftBound() const; ///< Checks if the platform has hit the left boundary.
    bool HitRightBound() const; ///< Checks if the platform has hit the right boundary.
    bool HitTopBound() const; ///< Checks if the platform has hit the top boundary.
    bool HitBottomBound() const; ///< Checks if the platform has hit the bottom boundary.

    /**
     * @brief Returns the movement vector for the platform.
     *
     * This method calculates the movement vector based on the platform's current direction.
     *
     * @return The movement vector for the platform.
     */
    Vector2 GetMovement() const;
};

#endif // MOVING_PLATFORM_H
