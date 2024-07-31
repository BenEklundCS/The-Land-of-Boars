//
// Created by ben on 7/15/24.
//

#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

#include "Platform.h"

class MovingPlatform : public Platform {
public:
    MovingPlatform(std::unique_ptr<Platform> platform, Vector2 boundsX, Vector2 boundsY, float speed, bool LR, bool UD);
    void Update() override;
private:
    // Position and bounderies
    Vector2 startingXY;
    Vector2 boundsX;
    Vector2 boundsY;
    // Desired movement behavior flags (LR/UD go here)
    bool moveLeftRight;
    bool moveUpDown;
    // Current movement direction flags
    bool movingRight = true;
    bool movingUp = true;
    // Desired movement speed
    float speed_;
    // Private methods
    void MoveLeftRight(float deltaTime);
    void MoveUpDown(float deltaTime);
    void SwapDirection();
    void Draw() override;
        // Collisions
    bool HitLeftBound();
    bool HitRightBound();
    bool HitTopBound();
    bool HitBottomBound();
};

#endif // MOVING_PLATFORM_H
