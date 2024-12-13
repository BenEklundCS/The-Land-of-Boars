//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVEL_H
#define PLATFORMER_LEVEL_H

#include <memory>
#include "../Entities/Player/Player.h"

class GameStateManager;

/**
 * @class Level
 * @brief Base class for game levels.
 *
 * The Level class serves as an abstract representation of a game level.
 * It is responsible for defining the logic to load and initialize
 * a `GameStateManager` object, which manages all entities and interactions
 * within the level. Subclasses of `Level` can define specific behavior and content
 * for different levels in the game.
 */
class Level {
public:
    /**
     * @brief Constructor for the Level class.
     *
     * Initializes the level and sets up any required resources.
     * This base constructor is intended to be called by derived classes.
     */
    Level();

    /**
     * @brief Retrieves the `GameStateManager` for the level.
     *
     * This method is intended to be overridden by subclasses.
     * It returns the `GameStateManager` associated with the specific level,
     * which contains the game state (e.g., entities, tiles, and objects).
     *
     * @return A pointer to the `GameStateManager` for the level.
     */
    virtual GameStateManager* GetGameState();

    /**
     * @brief Destructor for the Level class.
     *
     * Ensures that any dynamically allocated resources associated with the level
     * are properly released.
     */
    ~Level();
};

#endif //PLATFORMER_LEVEL_H
