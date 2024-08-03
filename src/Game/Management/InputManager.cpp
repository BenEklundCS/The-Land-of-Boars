//
// Created by ben on 6/10/24.
//

#include "../../../include/Game/Management/InputManager.h"
#include "../../../include/Platform/Engine.h"


void InputManager::HandleUserInput() {
    HandlePlayerInput();
    HandleUIInput();
    HandleDebugInput();
}

#pragma region helper functions

void InputManager::HandlePlayerInput() {
    if (IsKeyDown(KEY_LEFT)) playerCommands.leftCommand->Execute(player_); // move left on left keypress
    if (IsKeyDown(KEY_RIGHT)) playerCommands.rightCommand->Execute(player_); // move right on right keypress
    if (IsKeyPressed(KEY_A)) playerCommands.attackCommand->Execute(player_);
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && player_->CanJump())
        playerCommands.jumpCommand->Execute(player_); // make the player jump if can jump
}

void InputManager::HandleUIInput() {
    // ?
}

void InputManager::HandleDebugInput() {
    if (IsKeyPressed(KEY_B)) Engine::GetSettings()->renderRedBorders = !Engine::GetSettings()->renderRedBorders;
    if (IsKeyPressed(KEY_D)) Engine::GetSettings()->displayDebug = !Engine::GetSettings()->displayDebug;

}

#pragma endregion


