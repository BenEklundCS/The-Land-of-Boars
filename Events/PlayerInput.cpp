//
// Created by ben on 5/17/24.
//

#include "PlayerInput.h"

void HandlePlayerInput(Vector2 *position) {
    if (IsKeyDown(KEY_A)) {
        position->x -= 25;
    }
    if (IsKeyDown(KEY_D)) {
        position->x += 25;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        position->y -= 450;
    }
}