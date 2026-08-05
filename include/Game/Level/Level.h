//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_LEVEL_H
#define PLATFORMER_LEVEL_H

#include <memory>
#include "../Entities/Player/Player.h"
#include "LevelDef.h"

class GameStateManager;

/**
 * @class Level
 * @brief Builds a playable GameStateManager from a LevelDef.
 *
 * Levels used to be C++ subclasses with hardcoded constructor calls, so adding
 * one meant writing code. A Level is now just data: a tilemap for geometry and
 * an entity file for spawns, which is what makes levels authorable (by hand, by
 * the in-game editor, or generated) without touching the engine.
 */
class Level {
public:
    /**
     * @brief Constructs a level from its definition. Nothing is loaded yet.
     */
    explicit Level(LevelDef def);

    /**
     * @brief Builds the level and returns the populated game state.
     *
     * Resets the GameStateManager singleton first, so building a level never
     * inherits the previous level's entities, tiles or camera.
     *
     * @return The game state for this level, ready to be played.
     */
    [[nodiscard]] GameStateManager* Build() const;

    /**
     * @brief The level's definition (name and file paths).
     */
    [[nodiscard]] const LevelDef& GetDef() const { return def_; }

    ~Level();

private:
    LevelDef def_;

    /**
     * @brief Turns one parsed spawn record into a live game object.
     */
    static void ApplySpawn(GameStateManager* gameState, const EntitySpawn& spawn);
};

#endif //PLATFORMER_LEVEL_H
