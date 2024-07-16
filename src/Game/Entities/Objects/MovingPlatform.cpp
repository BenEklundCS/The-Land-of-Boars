//
// Created by ben on 7/15/24.
//

#include "../../../../include/Game/Entities/Objects/MovingPlatform.h"

// Constructor for MovingPlatform, initializing the base Platform class using an existing Platform object
MovingPlatform::MovingPlatform(const Platform& platform, Vector2 bounds, bool LR, bool UD)
        : Platform(platform), bounds(bounds), moveLeftRight(LR), moveUpDown(UD) {

}

void MovingPlatform::Update() {
    // Implement the logic for updating the moving platform
    float deltaTime = GetFrameTime();
    if (moveUpDown) {
        if (movingUp && )
    }
}
