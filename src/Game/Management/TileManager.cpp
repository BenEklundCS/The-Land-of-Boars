//
// Created by ben on 5/30/24.
//

#include "../../../include/Game/Management/TileManager.h"
#include "../../../include/Platform/Globals.h"
#include "../../../include/Game/Management/GameStateManager.h"
#include <cmath>

/**
 * @brief Initializes the tile grid based on a 2D vector of integers.
 *
 * This function populates the `tiles_` vector with tiles based on the provided `tileMap`.
 * Each integer in the `tileMap` corresponds to a specific tile type:
 *   - 0: Empty (nullptr).
 *   - 1: DIRT tile.
 *   - 2: GRASS tile.
 * The world-space position of each tile is calculated using its grid indices, tile
 * dimensions, and overlap adjustments. This function also ensures that the grid
 * dimensions match the input map.
 *
 * @param tileMap A 2D vector of integers representing the tile types.
 */
void TileManager::CreateTiles(const std::vector<std::vector<int>> tileMap) {
    tiles_.resize(tileMap.size());
    for (int i = 0; i < tileMap.size(); ++i) {
        tiles_[i].resize(tileMap[i].size());
    }

    for (int i = 0; i < tileMap.size(); ++i) {
        for (int j = 0; j < tileMap[i].size(); ++j) {
            constexpr int tile_overlap = 6;
            auto tileX = static_cast<float>(j * (TILE_LENGTH - tile_overlap));
            auto tileY = static_cast<float>(i * (TILE_LENGTH - tile_overlap));

            switch (tileMap[i][j]) {
                case 0:
                    tiles_[i][j] = nullptr;
                break;
                case 1:
                    tiles_[i][j] = std::make_unique<Tile>(tileX, tileY, TILE_DIRT_TEXTURE, tileMap[i][j]);
                break;
                case 2:
                    tiles_[i][j] = std::make_unique<Tile>(tileX, tileY, TILE_GRASS_TEXTURE, tileMap[i][j]);
                break;
                default:
                    TraceLog(LOG_FATAL, "Unknown tile type was passed to TileManager::CreateTiles()");
            }
        }
    }
}


/**
 * @brief Retrieves the grid position of a tile at a given mouse position in world space.
 *
 * This function calculates the grid indices of a tile based on the mouse's world-space
 * coordinates. It accounts for tile dimensions, scaling factors, and overlap adjustments.
 * If the calculated indices are out of bounds, an invalid position is returned.
 *
 * @param x The x-coordinate of the mouse in world space.
 * @param y The y-coordinate of the mouse in world space.
 * @return Vector2 The grid position of the tile as {tileX, tileY}, or {-1, -1} if out of bounds.
 */
Vector2 TileManager::GetTileAt(float x, float y) const {
    const auto tilePos = WorldToTile(x, y);
    const int tileX = static_cast<int>(tilePos.x);

    if (const int tileY = static_cast<int>(tilePos.y); tileY >= 0 && tileY < tiles_.size() && tileX >= 0 && tileX < tiles_[tileY].size()) {
        TraceLog(LOG_INFO, "Mouse (%f, %f) -> Tile Grid Pos: (%d, %d)", x, y, tileX, tileY);
        return tilePos;
    }

    TraceLog(LOG_WARNING, "Mouse position (%f, %f) is out of bounds", x, y);
    return Vector2{-1, -1};
}

/**
 * @brief Retrieves the current tile width, accounting for scale and overlap in the grid.
 *
 * @return Float, the width of the tile.
 */
float TileManager::GetTileWidth() {
    return (TILE_LENGTH - TILE_OVERLAP) * WINDOW_SCALE_FACTOR_X;
}

/**
 * @brief Retrieves the current tile height, accounting for scale and overlap in the grid.
 *
 * @return Float, the height of the tile.
 */
float TileManager::GetTileHeight() {
    return (TILE_LENGTH - TILE_OVERLAP) * WINDOW_SCALE_FACTOR_Y;
}

/**
 * @brief Retrieves a tile given world coordinates as input.
 * @param worldX, the input X coordinate
 * @param worldY, the input Y coordinate
 * @return Vector2, the position of the tile in the grid.
 */
Vector2 TileManager::WorldToTile(float worldX, float worldY) {
    return {
            (worldX + GetTileWidth() / 2) / GetTileWidth(),
            (worldY + GetTileHeight() / 2) / GetTileHeight()
    };
}

/**
 * @brief Retrieves a tile position given its indices.
 * @param tileX, the input X index
 * @param tileY, the input Y index
 * @return Vector2, the position of the tile in the world.
 */
Vector2 TileManager::TileToWorld(int tileX, int tileY) {
    return {
            tileX * GetTileWidth(),
            tileY * GetTileHeight()
    };
}


/**
 * @brief Updates or removes a tile at the specified grid position.
 *
 * This function modifies the tile at the given grid coordinates. If `tileType` is 0, the
 * tile is set to nullptr, effectively removing it. Otherwise, a new tile of the specified
 * type is created at the given position, using the appropriate texture.
 *
 * @param x The x-coordinate of the grid position.
 * @param y The y-coordinate of the grid position.
 * @param tileType The type of tile to set:
 *   - 0: Remove the tile (nullptr).
 *   - 1: Create a new DIRT tile.
 *   - 2: Create a new GRASS tile.
 */
void TileManager::SetTileAt(const int x, const int y, const int tileType) {
    // Calculate the dimensions of each tile
    const float tileWidth = GetTileWidth();
    const float tileHeight = GetTileHeight();
    // Validate grid indices
    if (y >= 0 && y < tiles_.size() && x >= 0 && x < tiles_[y].size()) {
        if (tileType == 0) {
            // Remove the tile
            TraceLog(LOG_INFO, "Deleting tile at (%d, %d)", x, y);
            tiles_[y][x].reset(); // Safely delete the existing tile
        }
        else if (tileType == 1) {
            // Create a new dirt tile
            TraceLog(LOG_INFO, "Creating dirt tile at (%d, %d)", x, y);
            tiles_[y][x].reset(); // Reset the unique_ptr to clear any existing tile
            tiles_[y][x] = std::make_unique<Tile>(
                    static_cast<float>(x * tileWidth),
                    static_cast<float>(y * tileHeight),
                    TILE_DIRT_TEXTURE, tileType); // Use appropriate texture for dirt
            TraceLog(LOG_INFO, "TileManager::SetTileAt: (%d, %d) set to dirt tile at %p", x, y, tiles_[y][x].get());
        }
        else if (tileType == 2) {
            // Create a new grass tile
            TraceLog(LOG_INFO, "Creating grass tile at (%d, %d)", x, y);
            tiles_[y][x].reset(); // Reset the unique_ptr to clear any existing tile
            tiles_[y][x] = std::make_unique<Tile>(
                    static_cast<float>(x * tileWidth),
                    static_cast<float>(y * tileHeight),
                    TILE_GRASS_TEXTURE, tileType); // Use appropriate texture for grass
            TraceLog(LOG_INFO, "TileManager::SetTileAt: (%d, %d) set to grass tile at %p", x, y, tiles_[y][x].get());
        }
        else {
            // Handle unrecognized tile types
            TraceLog(LOG_WARNING, "Unhandled tileType: %d", tileType);
        }
    }
    else {
        // Log out-of-bounds indices
        TraceLog(LOG_WARNING, "SetTileAt: Out-of-bounds indices (%d, %d)", x, y);
    }
}


// Return the tiles_ 2d array.
const std::vector<std::vector<std::unique_ptr<Tile>>>& TileManager::GetTiles() const {
    return tiles_;
}


// Constructor
TileManager::TileManager(Vector2 position) {
    this->position_ = position;
}
