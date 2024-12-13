//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVELONE_H
#define PLATFORMER_LEVELONE_H

#include "../Entities/Objects/Tile.h"
#include "../Entities/Monsters/Boar.h"
#include "Level.h"

/**
 * @class LevelOne
 * @brief A concrete implementation of the Level class for the first level of the game.
 *
 * LevelOne is a child class of the abstract Level class and represents the first playable level
 * in the game. This class is responsible for initializing and managing the state of the first level,
 * including its GameStateManager, objects, tiles, and entities specific to Level One.
 */
class LevelOne : public Level {
public:
    /**
     * @brief Retrieves the GameStateManager for Level One.
     *
     * This method overrides the pure virtual GetGameState method from the Level base class
     * to provide the specific GameStateManager instance for Level One.
     *
     * @return A pointer to the GameStateManager object managing Level One.
     */
    GameStateManager* GetGameState() override;
};

#endif //PLATFORMER_LEVELONE_H
