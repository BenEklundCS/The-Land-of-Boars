//
// Created by ben on 5/28/24.
//

#ifndef PLATFORMER_ENGINE_H
#define PLATFORMER_ENGINE_H

#include <vector>
#include <memory>
#include <raylib.h>
#include "Renderer.h"
#include "../Platform/GUI.h"
#include "../Game/Level/Level.h"
#include "../Game/Entities/UI/Button.h"

class GameStateManager;

/**
 * @file Engine.h
 * @brief Defines the `Engine` class responsible for managing the core game loop, loading levels,
 *        and controlling the overall flow of the game.
 *
 * This file also defines `EngineSettings` and `GameScreen` enums, which configure the behavior
 * and state transitions of the game engine.
 */

/**
 * @struct EngineSettings
 * @brief Configuration settings for the game engine.
 *
 * This structure contains options to enable or disable specific features, such as rendering debug information
 * or displaying visual aids like hitbox borders.
 */
struct EngineSettings {
    bool renderRedBorders = false; /**< Toggles the rendering of red borders around objects for debugging. */
    bool displayDebug = false; /**< Toggles the display of the debug GUI (ImGui overlay). */
};

/**
 * @enum GameScreen
 * @brief Represents the different screens or states the game can display.
 */
enum GameScreen {
    TITLE,    /**< Title screen displayed at the start of the game. */
    GAME,     /**< Main gameplay screen. */
    GAMEOVER  /**< Game Over screen displayed when the player loses. */
};

/**
 * @class Engine
 * @brief The main game engine responsible for:
 *        - Starting the game.
 *        - Loading levels.
 *        - Controlling the main game loop and screen transitions.
 *        - Managing the renderer and debugging tools.
 *
 * The `Engine` class takes ownership of `GameStateManager` objects to control and render the game state.
 */
class Engine {
private:
    std::unique_ptr<Button> startButton_;
    std::vector<std::unique_ptr<Level>> levels; /**< Stores the loaded levels for the game. */
    int curr = 0; /**< Tracks the current level being played. */

    static std::unique_ptr<EngineSettings> settings; /**< Singleton settings object. */

    GameScreen currentScreen = TITLE; /**< Tracks the current screen being displayed. */

    /**
     * @brief Loads all game levels into memory.
     */
    void LoadLevels();

    /**
     * @brief Helper method for creating a button and registering a callback function.
     */
    void CreateStartButton();
    /**
     * @brief Renders the Title screen.
     */
    void RenderTitleScreen() const;

    /**
     * @brief Renders the Game screen.
     */
    static void RenderGameScreen(GameStateManager* scene) ;

    /**
    * @brief Main game loop.
    */
    void GameLoop(GameStateManager* scene) const;

    /**
     * @brief Renders the Game Over screen.
     */
    static void RenderGameOverScreen();

    static bool shouldExit_; /**< Tracks whether the game should exit. */

public:
    /**
     * @brief Default constructor for the `Engine`.
     */
    Engine();

    /**
     * @brief Starts the game by initializing settings, loading levels, and displaying screens sequentially.
     */
    void StartGame();

    /**
     * @brief Provides access to the singleton `EngineSettings` object.
     * @return Pointer to the `EngineSettings` instance.
     */
    static EngineSettings* GetSettings() {
        return settings.get();
    }

    /**
     * @brief Destructor for the `Engine`.
     */
    ~Engine();

    static void StopGame();
};

#endif //PLATFORMER_ENGINE_H