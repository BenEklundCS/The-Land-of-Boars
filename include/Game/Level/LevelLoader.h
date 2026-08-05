//
// Created by ben on 8/4/24.
//

#ifndef PLATFORMER_LEVELLOADER_H
#define PLATFORMER_LEVELLOADER_H

#include <fstream>
#include <vector>
#include <string>
#include "../../../include/Game/Entities/Objects/Tile.h"
#include "LevelDef.h"

/**
 * @class LevelLoader
 * @brief Utility class for loading levels from files.
 *
 * The LevelLoader class provides a static method to load a level configuration
 * from a file and convert it into a 2D integer array. Each integer in the array
 * represents a specific tile or object type within the game world.
 */
class LevelLoader {
public:
    /**
     * @brief Loads a level from the specified file path.
     *
     * This method reads a file containing a 2D grid representation of the level.
     * Each line of the file corresponds to a row in the level, and each character
     * in the line is converted into an integer representing a tile type.
     *
     * @param filePath The path to the level file.
     * @return A 2D vector of integers representing the tile map for the level.
     *         Each integer corresponds to a specific tile type.
     * @note If the file cannot be opened, an empty 2D vector is returned, and an
     *       error is logged.
     */
    static std::vector<std::vector<int>> LoadLevel(const std::string& filePath);

    /**
    * @brief Saves a level to file at the specified file path.
    *
    *
    * @param tiles The list of tiles to save. Note: unique_ptrs are safely accessed with .get()
    * @param filePath The path to save file.
    */
    static void SaveLevel(const std::vector<std::vector<std::unique_ptr<Tile>>> &tiles, const std::string &filePath);

    /**
     * @brief Resolves a repo-relative asset path against the likely working directories.
     *
     * Paths used to be hardcoded as "../Levels/..", which only resolved when the
     * game was launched from inside the build directory. This tries the
     * plausible roots so the game runs from the repo root, the build dir, or a
     * packaged layout.
     *
     * @param relativePath e.g. "Levels/map_level_one.txt".
     * @return The first candidate that exists, or the input unchanged if none do.
     */
    static std::string ResolvePath(const std::string& relativePath);

    /**
     * @brief Parses a level's entity file into spawn records.
     *
     * Format is one entity per line: `type x y [w h] [arg]`. Blank lines and
     * lines starting with '#' are ignored. Unknown types are logged and skipped
     * rather than aborting, so a typo costs one entity, not the level.
     *
     * @param filePath Path to the entity file (resolved internally).
     * @return The parsed spawns, empty if the file is missing.
     */
    static std::vector<EntitySpawn> LoadEntities(const std::string& filePath);
};

#endif //PLATFORMER_LEVELLOADER_H
