//
// Created by ben on 6/10/24.
//

#ifndef PLATFORMER_INPUTMANAGER_H
#define PLATFORMER_INPUTMANAGER_H

#include "GameStateManager.h"
#include "../Entities/Player/Player.h"
#include "../Events/Commands/PlayerCommands.h"
#include "../Events/Commands/EditorCommands.h"

/**
 * @file InputManager.h
 * @brief Handles all user input for the game, including player commands, UI interactions, and debug controls.
 *
 * The `InputManager` class is responsible for capturing and processing user inputs,
 * delegating actions to the appropriate game systems (e.g., player movement, UI navigation, debug controls).
 */

/**
 * @class InputManager
 * @brief Manages and processes all user input for the game.
 *
 * The `InputManager` captures input events and dispatches them to the appropriate handlers,
 * such as player commands, UI actions, or debug mode toggles. It also supports specialized input
 * for level editing and camera movement in editor mode.
 */
class InputManager {
private:
    Player* player_; ///< Pointer to the player object for handling input.
    EngineSettings& settings_; ///< Reference to engine settings for input customization.

    /**
     * @brief Handles input specifically for the player, executing associated commands.
     */
    void HandlePlayerInput() const;

    /**
     * @brief Handles input for UI interactions, such as menu navigation.
     */
    static void HandleUIInput();

    /**
     * @brief Handles input for debugging purposes, such as toggling debug information.
     */
    static void HandleDebugInput();

    /**
     * @brief Handles camera movement for the level editor.
     * @param camera Reference to the game's camera.
     */
    static void HandleEditorMovement(Camera2D& camera);

    /**
     * @brief Handles actions for level editing, such as placing or removing tiles.
     * @param gameState Pointer to the current game state.
     * @param camera Reference to the game's camera.
     */
    static void HandleEditorActions(GameStateManager* gameState, Camera2D& camera);
public:
    /**
     * @brief Constructs an InputManager instance.
     * @param player Pointer to the player object.
     * @param settings Reference to the engine settings for input configuration.
     */
     explicit InputManager(Player* player, EngineSettings& settings)
     : player_(player), settings_(settings) {
     }

    /**
     * @brief Handles all user input during gameplay, including player commands and UI interactions.
     */
    void HandleUserInput() const;

    /**
     * @brief Public static interface for handling the escape key and other global commands.
     */
    static void HandleEngineInput();

    /**
    * @brief Handles user input specific to the level editor, including camera and tile actions.
    * @param camera Reference to the game's camera.
    */
    static void HandleEditorInput(Camera2D& camera);
};

#endif //PLATFORMER_INPUTMANAGER_H
