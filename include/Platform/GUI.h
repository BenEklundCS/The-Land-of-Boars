//
// Created by ben on 6/4/24.
//

#ifndef PLATFORMER_DEBUGGUI_H
#define PLATFORMER_DEBUGGUI_H

#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"
#include "../Game/Management/GameStateManager.h"

/**
 * @file GUI.h
 * @brief Provides debugging tools and utilities for rendering and interacting with in-game debug information.
 *
 * The `GUI` class uses ImGui to render an interactive debugging interface during gameplay.
 * It is primarily used to display player data, object counts, and other game-related information.
 */

/**
 * @class GUI
 * @brief Handles the initialization and rendering of the debug GUI overlay.
 *
 * The `GUI` class provides static methods to initialize and render the debugging interface,
 * using ImGui and rlImGui integrations. It works in conjunction with the `GameStateManager` to
 * display real-time information about the game state.
 */
class GUI {
private:
    // GUI stores the user's current selected block, this value is updated when buttons are clicked
    static int blockSelection_;
public:
    /**
     * @brief Initializes the ImGui system for rendering the debug GUI.
     *
     * This method sets up ImGui using `rlImGuiSetup` and prepares it for use in the game.
     * It should be called once during the engine initialization phase.
     */
    static void InitGui();

    /**
     * @brief Renders the debug GUI using data from the current game state.
     * @param gameState Pointer to the `GameStateManager` containing the current game data.
     *
     * The GUI displays information such as:
     * - Player position, velocity, health, and state.
     * - Object counts (players, monsters, platforms, etc.).
     * - Debugging utilities for observing gameplay elements in real-time.
     */
    static void DrawDebugGUI(GameStateManager* gameState);

    /**
     * @brief Renders the level editor GUI giving the user tools to edit the level.
     *
     * The GUI displays:
     * - A block selector, for selecting between air, dirt, and grass blocks for placement in the level.
     */
    static void DrawEditorGUI();

    /**
     * @brief Gets the current block selection from the GUI.
     * @return int - 0 for air, 1 for dirt, 2 for grass.
     */
    static int GetBlockSelection();

    /**
     * @brief Convert a PlayerState enum to a string representation.
     *
     * @param state The PlayerState to convert.
     * @return std::string The string representation of the player state.
     */
    static std::string PlayerStateToString(PlayerState state);

    /**
    * @brief Convert a Raylib Color struct to a string representation.
    *
    * @param color The Color struct to convert.
    * @return std::string The string representation of the color.
    */
    static std::string ColorToString(Color color);
};

#endif //PLATFORMER_DEBUGGUI_H
