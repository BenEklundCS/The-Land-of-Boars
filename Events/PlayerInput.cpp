//
// Created by ben on 5/17/24.
//

#include "PlayerInput.h"

void HandlePlayerInput(Vector2 *position) {
    if (IsKeyDown(KEY_A)) { // move left
        position->x -= 25;
    }
    if (IsKeyDown(KEY_D)) { // move right
        position->x += 25;
    }
    if (IsKeyPressed(KEY_SPACE)) { // jump
        position->y -= 450;
    }
}