//
// Created by ben on 6/10/24.
//

#include "../../../include/Game/Management/InputManager.h"
#include "../../../include/Platform/Engine.h"

/**
 * @brief Handles all user input during gameplay, UI interactions, and debugging.
 *
 * This function acts as the main entry point for processing user input. It delegates
 * tasks to helper functions based on the type of input being handled.
 */
void InputManager::HandleUserInput() const {
    HandlePlayerInput();
    HandleUIInput();
    HandleDebugInput();
}

#pragma region helper functions

/**
 * @brief Handles player-related input during gameplay.
 *
 * Processes keypresses for movement, attacks, and jumps. Ensures that commands
 * are executed only when valid conditions (e.g., CanJump) are met.
 */
void InputManager::HandlePlayerInput() const {
    if (IsKeyDown(KEY_LEFT)) LeftCommand::Execute(player_); // move left on left keypress
    if (IsKeyDown(KEY_RIGHT)) RightCommand::Execute(player_); // move right on right keypress
    if (IsKeyPressed(KEY_A)) AttackCommand::Execute(player_);
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && player_->CanJump())
        JumpCommand::Execute(player_); // make the player jump if can jump
}

/**
 * @brief Handles input related to UI and game state transitions.
 *
 * Detects input for UI interactions, such as toggling to the editor mode
 * and resetting the camera for proper navigation.
 */
void InputManager::HandleUIInput() {
    auto gameState = GameStateManager::GetInstance();
    if (IsKeyPressed(KEY_L)) {
        gameState->SetMode(MODE_EDITOR);
        gameState->InitCamera(); // reset the camera
    }
}

/**
 * @brief Handles debug-related input for toggling debug settings.
 *
 * Processes keypresses to enable or disable rendering debug visuals and debug information.
 */
void InputManager::HandleDebugInput() {
    if (IsKeyPressed(KEY_B)) Engine::GetSettings()->renderRedBorders = !Engine::GetSettings()->renderRedBorders;
    if (IsKeyPressed(KEY_D)) Engine::GetSettings()->displayDebug = !Engine::GetSettings()->displayDebug;
}

/**
 * @brief Handles all input in editor mode, including camera movement and tile manipulation.
 *
 * This function processes editor-specific inputs, allowing the user to move the camera,
 * modify tiles, and switch back to game mode when needed.
 *
 * @param camera The camera used to navigate the editor view.
 */
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

/**
 * @brief Handles editor-specific actions such as adding, deleting, or modifying tiles.
 *
 * Processes mouse inputs to interact with the tile map, including adding and deleting
 * tiles in the scene. Updates the game state to reflect changes.
 *
 * @param gameState Pointer to the game state manager.
 * @param camera The camera used to determine world-space positions.
 */
void InputManager::HandleEditorActions(GameStateManager* gameState, Camera2D& camera) {
    try {
        TileManager& tileManager = gameState->GetTileManager();

        // Edit
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            auto mousePos = GetMousePosition();
            auto worldPosition = GetScreenToWorld2D(mousePos, camera);

            TraceLog(LOG_INFO, "Mouse Position: Screen (%f, %f), World (%f, %f)",
                     mousePos.x, mousePos.y, worldPosition.x, worldPosition.y);

            auto tilePosition = tileManager.GetTileAt(worldPosition.x, worldPosition.y);

            int blockSelection = GUI::GetBlockSelection();

            TraceLog(LOG_INFO, "BLOCK SELECTION: %d", blockSelection);

            tileManager.SetTileAt((int)tilePosition.x, (int)tilePosition.y, blockSelection); // Set the tile
            TraceLog(LOG_INFO, "Tile at: %f, %f", tilePosition.x, tilePosition.y);
        }

        // Print tile position (debug)
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                auto mousePos = GetMousePosition();
                auto worldPosition = GetScreenToWorld2D(mousePos, camera);

                TraceLog(LOG_INFO, "Mouse Position: Screen (%f, %f), World (%f, %f)",
                         mousePos.x, mousePos.y, worldPosition.x, worldPosition.y);

                auto tilePosition = tileManager.GetTileAt(worldPosition.x, worldPosition.y);
                TraceLog(LOG_INFO, "Tile at: %f, %f", tilePosition.x, tilePosition.y);
            }
        }

    } catch (const std::exception& e) {
        TraceLog(LOG_ERROR, "Error accessing TileManager: %s", e.what());
    }
}

/**
 * @brief Handles camera movement in the editor.
 *
 * Processes keypresses to pan the camera view. Movement speed is increased
 * when the SHIFT key is held down.
 *
 * @param camera The camera to be moved.
 */
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


