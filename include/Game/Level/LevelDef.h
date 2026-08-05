//
// Data-driven level definitions.
//

#ifndef PLATFORMER_LEVELDEF_H
#define PLATFORMER_LEVELDEF_H

#include <string>
#include <vector>

/**
 * @struct EntitySpawn
 * @brief One line from a level's entity file.
 *
 * Deliberately generic - a type name plus up to four numbers and an optional
 * string argument covers every entity the game currently spawns, and adding a
 * new one means handling a new type string rather than changing the format.
 */
struct EntitySpawn {
    std::string type;   ///< "player", "goal", "boar", "bee", "snail", "tree", "coin", "platform".
    float x = 0.0f;
    float y = 0.0f;
    float w = 0.0f;     ///< Width, or pacing/dimension arg depending on type.
    float h = 0.0f;
    std::string arg;    ///< Optional extra (e.g. tree texture name).
};

/**
 * @struct LevelDef
 * @brief Everything needed to build a level, with no C++ per level.
 *
 * Previously each level was a hand-written C++ class with hardcoded
 * constructor calls, which meant a new level required new code. Levels are now
 * pure data: a tilemap for geometry and an entity file for spawns.
 */
struct LevelDef {
    std::string name;          ///< Display name.
    std::string tilemapPath;   ///< Repo-relative, e.g. "Levels/map_level_one.txt".
    std::string entitiesPath;  ///< Repo-relative, e.g. "Levels/level_one.entities.txt".
};

#endif //PLATFORMER_LEVELDEF_H
