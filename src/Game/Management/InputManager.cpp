//
// Created by ben on 6/10/24.
//

#include "../../../include/Game/Management/InputManager.h"

#include "../../../include/Game/Events/Commands/EditorCommands.h"
#include "../../../include/Game/Events/Commands/EngineCommands.h"
#include "../../../include/Game/Level/LevelLoader.h"
#include "../../../include/Game/Level/LevelEditor.h"
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
    // always handle Engine Input while User Input is being handled.
    HandleEngineInput();
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
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)))
        JumpCommand::Execute(player_); // make the player jump if can jump
}

/**
 * @brief Handles input related to UI and game state transitions.
 *
 * Detects input for UI interactions, such as toggling to the editor mode
 * and resetting the camera for proper navigation.
 * NOTE: We check to exit game here, as I do not currently want to allow it to be this easy to exit the game in editor-mode.
 * I have lost work multiple times editing levels.
 */
void InputManager::HandleUIInput() {
    auto gameState = GameStateManager::GetInstance();
    if (IsKeyPressed(KEY_E)) {
        EnterEditorCommand::Execute(gameState);
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
    const auto gameState = GameStateManager::GetInstance();
    HandleEditorActions(gameState, camera);

    if (IsKeyPressed(KEY_E)) {
        ExitEditorCommand::Execute(gameState);
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
        // Make sure ImGUI doesn't want to capture the mouse click before handling it
        // ImGui::GetIO().WantCaptureMouse worked on Windows, did not work as expected on Linux.
        // This function seems to work better anyway - although it is not suggested for use this way.
        if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
            // Lambda function returns True if left mouse button and left control are both pressed down
            auto CtrlAndLeftMouseDown = [&]() {
                return IsMouseButtonDown(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_CONTROL);
            };
            // Place tile command
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || CtrlAndLeftMouseDown()) {
                PlaceTileCommand::Execute();
            }

            // Print tile position (debug)
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                PrintTileCommand::Execute();
            }
        }
        // Save level to file
        if (IsKeyPressed(KEY_S))
            SaveLevelCommand::Execute();
        // Load level from file
        if (IsKeyPressed(KEY_L))
            LoadLevelCommand::Execute();

    } catch (const std::exception& e) {
        TraceLog(LOG_ERROR, "Error accessing TileManager: %s", e.what());
    }
}

constexpr float CAMERA_MOVE_SPEED = 10.0f;
constexpr float CAMERA_FAST_MULTIPLIER = 5.0f;
constexpr float CAMERA_VERY_FAST_MULTIPLIER = 10.0f;

/**
 * @brief Handles camera movement in the editor.
 *
 * Processes keypresses to pan the camera view. Movement speed is increased
 * when the SHIFT key is held down.
 *
 * @param camera The camera to be moved.
 */
void InputManager::HandleEditorMovement(Camera2D& camera) {
    auto moveCamera = [&](int key, float& target, float amount) {
        if (IsKeyDown(key)) {
            if (IsKeyDown(KEY_LEFT_SHIFT))
                amount *= CAMERA_FAST_MULTIPLIER;
            else if (IsKeyDown(KEY_LEFT_ALT))
                amount *= CAMERA_VERY_FAST_MULTIPLIER;
            target += amount;
        }
    };

    moveCamera(KEY_UP, camera.target.y, -CAMERA_MOVE_SPEED);
    moveCamera(KEY_DOWN, camera.target.y, CAMERA_MOVE_SPEED);
    moveCamera(KEY_LEFT, camera.target.x, -CAMERA_MOVE_SPEED);
    moveCamera(KEY_RIGHT, camera.target.x, CAMERA_MOVE_SPEED);
}

void InputManager::HandleEngineInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        StopGameCommand::Execute();
    }
}


#pragma endregion


