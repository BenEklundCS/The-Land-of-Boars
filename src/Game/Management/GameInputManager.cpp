//
// Created by ben on 6/10/24.
//

#include "../../../include/Game/Management/GameInputManager.h"
#include "../../../include/Platform/Engine.h"

void GameInputManager::HandleUserInput() {
    HandlePlayerInput();
    HandleUIInput();
    HandleDebugInput();
}

#pragma region helper functions

void GameInputManager::HandlePlayerInput() {
    if (IsKeyDown(KEY_LEFT)) player_->MoveLeft(); // move left on left keypress
    if (IsKeyDown(KEY_RIGHT)) player_->MoveRight(); // move right on right keypress
    if (player_->CanJump()) player_->Jump(); // make the player jump if can jump
}

void GameInputManager::HandleUIInput() {

}

void GameInputManager::HandleDebugInput() {
    if (IsKeyPressed(KEY_B)) Engine::GetSettings()->renderRedBorders = !Engine::GetSettings()->renderRedBorders;
    if (IsKeyPressed(KEY_D)) Engine::GetSettings()->displayDebug = !Engine::GetSettings()->displayDebug;

}


#pragma endregion


