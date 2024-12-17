//
// Created by ben on 5/16/24.
//

#ifndef PLATFORMER_RENDERER_H
#define PLATFORMER_RENDERER_H

#include <vector>
#include "Window.h"
#include "raylib.h"
#include "Engine.h"

struct EngineSettings; /**< Forward declaration for EngineSettings structure. */
class GameStateManager; /**< Forward declaration for GameStateManager class. */

/**
 * @class Renderer
 * @brief Handles all rendering tasks for the game, including drawing game objects, backgrounds, and UI elements.
 *
 * The `Renderer` class provides a static interface for rendering different aspects of the game.
 * It interacts with the `GameStateManager` to retrieve the current game state and draws the scene accordingly.
 * It also supports rendering a title screen, level editor elements, and debug overlays like FPS counters.
 */
class Renderer {
private:
    /**
     * @brief Renders the game background.
     *
     * @param camera The camera used to determine the viewport for rendering the background.
     *
     * This method renders a scrolling or static background depending on the game's camera position.
     */
    static void RenderBackground(Camera2D camera);

    /**
     * @brief Renders the FPS counter.
     *
     * @param camera The camera used to determine where to position the FPS counter in the viewport.
     *
     * This method is used in debug mode to display the current frames per second.
     */
    static void RenderFPS(Camera2D camera);
public:
    /**
     * @brief Constructs a `Renderer` object.
     *
     * This constructor sets up the `Renderer` but does not initialize any specific resources.
     */
    Renderer();

    /**
     * @brief Draws the current game state.
     *
     * @param gameState Pointer to the `GameStateManager` containing the current game state.
     * @param settings Pointer to the `EngineSettings` structure for rendering options (e.g., debug overlays).
     *
     * This method is the main draw call for the game. It handles rendering all game objects, background,
     * UI elements, and optionally debug overlays like hitboxes.
     */
    static void Draw(GameStateManager* gameState, const EngineSettings* settings);

    /**
     * @brief Renders the title screen.
     *
     * This method handles rendering the game's title screen, including the title text, subtitle,
     * and any background or animation effects.
     */
    static void DrawTitleScreen();

    /**
     * @brief Destroys the `Renderer` object.
     *
     * This destructor ensures any resources or state used by the `Renderer` are properly cleaned up.
     */
    ~Renderer();
};

#endif //PLATFORMER_RENDERER_H
