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
 * @file DebugGUI.h
 * @brief Provides debugging tools and utilities for rendering and interacting with in-game debug information.
 *
 * The `DebugGUI` class uses ImGui to render an interactive debugging interface during gameplay.
 * It is primarily used to display player data, object counts, and other game-related information.
 */

/**
 * @class DebugGUI
 * @brief Handles the initialization and rendering of the debug GUI overlay.
 *
 * The `DebugGUI` class provides static methods to initialize and render the debugging interface,
 * using ImGui and rlImGui integrations. It works in conjunction with the `GameStateManager` to
 * display real-time information about the game state.
 */
class DebugGUI {
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
    static void DrawGui(GameStateManager* gameState);
};

#endif //PLATFORMER_DEBUGGUI_H
