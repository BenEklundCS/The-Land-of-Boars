//
// Created by ben on 5/30/24.
//

#ifndef PLATFORMER_TILEMANAGER_H
#define PLATFORMER_TILEMANAGER_H

#include <vector>
#include <unordered_map>
#include "../Entities/Objects/Tile.h"

/**
 * @file TileManager.h
 * @brief Manages and creates tiles for the game world.
 *
 * The `TileManager` class simplifies the management and creation of game tiles.
 * It uses a 2D array of integers to define the map layout and dynamically generates tile objects.
 * This class also supports querying and modifying tiles at specific positions.
 */

/**
 * @namespace std
 * @brief Adds a custom hash implementation for `std::pair<int, int>` to use as a key in unordered maps.
 *
 * This allows `std::unordered_map` to efficiently handle 2D coordinates as keys.
 */
namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        /**
         * @brief Hash function for a pair of integers.
         * @param p A pair of integers to hash.
         * @return A combined hash value for the pair.
         */
        size_t operator()(const std::pair<int, int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };
}

/**
 * @class TileManager
 * @brief Manages the creation and handling of tiles for the game.
 *
 * The `TileManager` provides functionality to generate tiles from a 2D array,
 * retrieve tile information based on positions, and dynamically update tiles in the game world.
 */
class TileManager {
private:
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles_; ///< 2D array of tile objects.
    Vector2 position_{}; ///< Position of the TileManager (used for offset or placement).

public:
    /**
     * @brief Constructor for the `TileManager`.
     * @param position The starting position of the TileManager (used as an origin for the tile grid).
     */
    TileManager(Vector2 position);

    /**
     * @brief Creates tiles from a 2D array of integers.
     * @param tileMap A 2D array where each integer represents a tile type.
     *
     * Each integer in `tileMap` corresponds to a tile, which will be instantiated and placed
     * based on its position in the array.
     */
    void CreateTiles(const std::vector<std::vector<int>> tileMap);

    /**
     * @brief Retrieves the tile type at a specific world position.
     * @param x The x-coordinate in world space.
     * @param y The y-coordinate in world space.
     * @return A `Vector2` representing the tile at the specified position.
     *
     * This method determines which tile exists at a given position in the world.
     */
    Vector2 GetTileAt(float x, float y) const;

    /**
     * @brief Sets or updates a tile at a specific position.
     * @param x The x-coordinate in world space.
     * @param y The y-coordinate in world space.
     * @param tileType The type of tile to set at the specified position.
     *
     * This method allows dynamic modifications to the tile map during gameplay.
     */
    void SetTileAt(const float x, const float y, const int tileType);

    /**
     * @brief Retrieves the internal 2D array of tiles.
     * @return A constant reference to the 2D vector of unique pointers to `Tile` objects.
     *
     * This is primarily used for rendering or external inspection of the tile grid.
     */
    const std::vector<std::vector<std::unique_ptr<Tile>>>& GetTiles() const;
};

#endif //PLATFORMER_TILEMANAGER_H
