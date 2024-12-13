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

void InputManager::HandleUIInput() {
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

void InputManager::HandleEditorInput(Camera2D& camera) {
    HandleEditorMovement(camera);
    auto gameState = GameStateManager::GetInstance();
    HandleEditorActions(gameState, camera);

    if (IsKeyPressed(KEY_L)) {
        gameState->SetMode(MODE_GAME);
        gameState->InitCamera(); // reset the camera
        // Reload tiles in case of any edits
       // gameState->SetTileManager();
    }

    HandleDebugInput();
}

void InputManager::HandleEditorActions(GameStateManager* gameState, Camera2D& camera) {
    try {
        TileManager& tileManager = gameState->GetTileManager();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            auto mousePos = GetMousePosition();
            auto worldPosition = GetScreenToWorld2D(mousePos, camera);

            TraceLog(LOG_INFO, "Mouse Position: Screen (%f, %f), World (%f, %f)",
                     mousePos.x, mousePos.y, worldPosition.x, worldPosition.y);

            auto tilePosition = tileManager.GetTileAt(worldPosition.x, worldPosition.y);
            TraceLog(LOG_INFO, "Tile at: %f, %f", tilePosition.x, tilePosition.y);
        }

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            auto mousePos = GetMousePosition();
            auto worldPosition = GetScreenToWorld2D(mousePos, camera);

            TraceLog(LOG_INFO, "Mouse Position: Screen (%f, %f), World (%f, %f)",
                     mousePos.x, mousePos.y, worldPosition.x, worldPosition.y);

            auto tilePosition = tileManager.GetTileAt(worldPosition.x, worldPosition.y);
            tileManager.SetTileAt(tilePosition.x, tilePosition.y, 0); // delete the clicked tile from the scene
            gameState->ReloadTiles(); // reflect the change across the gameState
            TraceLog(LOG_INFO, "Tile at: %f, %f", tilePosition.x, tilePosition.y);
        }

    } catch (const std::exception& e) {
        TraceLog(LOG_ERROR, "Error accessing TileManager: %s", e.what());
    }
}

void InputManager::HandleEditorMovement(Camera2D& camera) {
    if (IsKeyDown(KEY_UP)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            camera.target.y -= 30;
        }
        else {
            camera.target.y -= 10;
        }
    }
    if (IsKeyDown(KEY_DOWN)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            camera.target.y += 30;
        }
        else {
            camera.target.y += 10;
        }
    }
    if (IsKeyDown(KEY_LEFT)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            camera.target.x -= 30;
        }
        else {
            camera.target.x -= 10;
        }
    }
    if (IsKeyDown(KEY_RIGHT)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            camera.target.x += 30;
        }
        else {
            camera.target.x += 10;
        }
    }
}


#pragma endregion


