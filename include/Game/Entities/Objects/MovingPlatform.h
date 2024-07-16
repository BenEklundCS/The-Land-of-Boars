//
// Created by ben on 7/15/24.
//

#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

#include "Platform.h"

class MovingPlatform : public Platform {
public:
    MovingPlatform(const Platform& platform, Vector2 bounds, bool LR, bool UD);
    void Update() override;
private:
    Platform& initPlatform;
    Platform& currPlatform;
    Vector2 bounds;
    bool moveLeftRight;
    bool moveUpDown;
    bool movingRight = true;
    bool movingUp = true;
};

#endif // MOVING_PLATFORM_H
