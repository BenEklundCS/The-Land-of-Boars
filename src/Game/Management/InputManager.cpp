//
// Created by ben on 6/10/24.
//

#include "../../../include/Game/Management/InputManager.h"
#include "../../../include/Platform/Engine.h"

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
    auto gameState = GameStateManager::GetInstance();
    if (IsKeyPressed(KEY_L)) {
        gameState->SetMode(MODE_EDITOR);
        gameState->InitCamera(); // reset the camera
    }
}

void InputManager::HandleDebugInput() {
    if (IsKeyPressed(KEY_B)) Engine::GetSettings()->renderRedBorders = !Engine::GetSettings()->renderRedBorders;
    if (IsKeyPressed(KEY_D)) Engine::GetSettings()->displayDebug = !Engine::GetSettings()->displayDebug;
}

void InputManager::HandleEditorInput(Camera2D& camera) const {

    auto gameState = GameStateManager::GetInstance();

    if (IsKeyPressed(KEY_L)) {
        gameState->SetMode(MODE_GAME);
        gameState->InitCamera(); // reset the camera
    }

    if (IsKeyDown(KEY_UP)) {
        camera.target.y -= 10;
    }
    if (IsKeyDown(KEY_DOWN)) {
        camera.target.y += 10;
    }
    if (IsKeyDown(KEY_LEFT)) {
        camera.target.x -= 10;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        camera.target.x += 10;
    }
    HandleDebugInput();

    try {
        TileManager& tileManager = gameState->GetTileManager();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            auto mousePos = GetMousePosition();
            tileManager.SetTileAt(mousePos.x, mousePos.y, 1);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            auto mousePos = GetMousePosition();
            tileManager.SetTileAt(mousePos.x, mousePos.y, 0);
        }
    } catch (const std::exception& e) {
        TraceLog(LOG_ERROR, "Error accessing TileManager: %s", e.what());
    }

}


#pragma endregion


