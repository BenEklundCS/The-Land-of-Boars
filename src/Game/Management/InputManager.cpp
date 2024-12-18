//
// Created by ben on 6/10/24.
//

#include "../../../include/Game/Management/InputManager.h"

#include "../../../include/Game/Level/LevelLoader.h"
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
    if (IsKeyPressed(KEY_E)) {
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

    if (IsKeyPressed(KEY_E)) {
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

        // Make sure ImGUI doesn't want to capture the mouse click before handling it
        // ImGui::GetIO().WantCaptureMouse worked on Windows, did not work as expected on Linux.
        // This function seems to work better anyway - although it is not suggested for use this way.
        if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
            // Edit
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_CONTROL))) {
                auto mousePos = GetMousePosition();
                auto worldPosition = GetScreenToWorld2D(mousePos, camera);
                auto tilePosition = tileManager.GetTileAt(worldPosition.x, worldPosition.y);
                int blockSelection = GUI::GetBlockSelection();
                TraceLog(LOG_INFO, "BLOCK SELECTION: %d", blockSelection);
                tileManager.SetTileAt(static_cast<int>(tilePosition.x), static_cast<int>(tilePosition.y), blockSelection); // Set the tile
                gameState->ReloadTiles();
            }

            // Print tile position (debug)
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    auto mousePos = GetMousePosition();
                    auto worldPosition = GetScreenToWorld2D(mousePos, camera);
                    auto tilePosition = tileManager.GetTileAt(worldPosition.x, worldPosition.y);
                    TraceLog(LOG_INFO, "Tile at: %d, %d", static_cast<int>(tilePosition.x), static_cast<int>(tilePosition.y));
                }
            }
        }
        // Save level to file
        if (IsKeyPressed(KEY_S)) {
            TraceLog(LOG_INFO, "Saving level...");
            LevelLoader::SaveLevel(tileManager.GetTiles(), "../Levels/myLevel.txt");
        }

        // Load level from file
        if (IsKeyPressed(KEY_L)) {
            TraceLog(LOG_INFO, "Loading level...");
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
    // Lambda function for moving the camera`
    auto moveCamera = [&](int key, float& target, float amount) {
        if (IsKeyDown(key)) {
            if (IsKeyDown(KEY_LEFT_SHIFT))
                amount *= 5; // faster
            else if (IsKeyDown(KEY_LEFT_ALT))
                amount *= 10; // very fast
            target += amount;
        }
    };

    moveCamera(KEY_UP, camera.target.y, -10);
    moveCamera(KEY_DOWN, camera.target.y, 10);
    moveCamera(KEY_LEFT, camera.target.x, -10);
    moveCamera(KEY_RIGHT, camera.target.x, 10);
}


#pragma endregion


