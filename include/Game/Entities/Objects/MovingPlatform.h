//
// Created by ben on 7/15/24.
//

#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

#include "Platform.h"

class MovingPlatform : public Platform {
public:
    MovingPlatform(std::unique_ptr<Platform> platform, Vector2 boundsX, Vector2 boundsY, bool LR, bool UD);
    void Update() override;
private:
    Vector2 startingXY;
    Vector2 boundsX;
    Vector2 boundsY;
    bool moveLeftRight;
    bool moveUpDown;
    bool movingRight = true;
    bool movingUp = true;

    void Draw();
};

#endif // MOVING_PLATFORM_H
