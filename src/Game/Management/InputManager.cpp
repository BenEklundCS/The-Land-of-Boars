//
// Created by ben on 6/10/24.
//

#include "../../../include/Game/Management/InputManager.h"

#include "../../../include/Game/Events/Commands/EngineCommands.h"
#include "../../../include/Platform/Engine.h"
#include "../../../include/Platform/LevelEditor/LevelEditor.h"


void InputManager::HandleUserInput() const {
    HandlePlayerInput();
    HandleUIInput();
    HandleDebugInput();
}

#pragma region helper functions

void InputManager::HandlePlayerInput() const {
    if (IsKeyDown(KEY_LEFT)) LeftCommand::Execute(player_); // move left on left keypress
    if (IsKeyDown(KEY_RIGHT)) RightCommand::Execute(player_); // move right on right keypress
    if (IsKeyPressed(KEY_A)) AttackCommand::Execute(player_);
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && player_->CanJump())
        JumpCommand::Execute(player_); // make the player jump if can jump
}

void InputManager::HandleUIInput() const {
    // ?
    if (IsKeyPressed(KEY_L)) EditLevelCommand::Execute(levelEditor_);
}

void InputManager::HandleDebugInput() const {
    if (IsKeyPressed(KEY_B)) Engine::GetSettings()->renderRedBorders = !Engine::GetSettings()->renderRedBorders;
    if (IsKeyPressed(KEY_D)) Engine::GetSettings()->displayDebug = !Engine::GetSettings()->displayDebug;
}

#pragma endregion


