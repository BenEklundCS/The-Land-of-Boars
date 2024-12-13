//
// Created by ben on 5/30/24.
//

#include "../../../include/Game/Management/TileManager.h"
#include "../../../include/Platform/Globals.h"
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
            float tileX = static_cast<float>(j * (TILE_LENGTH - tile_overlap));
            float tileY = static_cast<float>(i * (TILE_LENGTH - tile_overlap));

            switch (tileMap[i][j]) {
                case 0:
                    tiles_[i][j] = nullptr;
                break;
                case 1:
                    tiles_[i][j] = std::make_unique<Tile>(tileX, tileY, TILE_DIRT_TEXTURE);
                break;
                case 2:
                    tiles_[i][j] = std::make_unique<Tile>(tileX, tileY, TILE_GRASS_TEXTURE);
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
    constexpr int tile_overlap = 6;

    // Calculate the effective tile dimensions (accounting for overlap and scaling)
    float tileWidth = (TILE_LENGTH - tile_overlap) * WINDOW_SCALE_FACTOR_X;
    float tileHeight = (TILE_LENGTH - tile_overlap) * WINDOW_SCALE_FACTOR_Y;

    // Adjust mouse coordinates for scaling (convert to world space if needed)
    float scaledX = x;
    float scaledY = y;

    // Calculate grid indices (center the calculation to the nearest tile)
    int tileX = static_cast<int>((scaledX + tileWidth / 2) / tileWidth);
    int tileY = static_cast<int>((scaledY + tileHeight / 2) / tileHeight);

    // Validate indices to ensure they're within bounds
    if (tileY >= 0 && tileY < tiles_.size() && tileX >= 0 && tileX < tiles_[tileY].size()) {
        // Log for debugging purposes
        TraceLog(LOG_INFO, "Mouse (%f, %f) -> Scaled Mouse (%f, %f) -> Tile Grid Pos: (%d, %d)",
                 x, y, scaledX, scaledY, tileX, tileY);

        // Return the tile indices as a Vector2
        return Vector2{static_cast<float>(tileX), static_cast<float>(tileY)};
    }

    // Handle out-of-bounds mouse positions
    TraceLog(LOG_WARNING, "Mouse position (%f, %f) is out of bounds", x, y);
    return Vector2{-1, -1}; // Return invalid vector for out-of-bounds
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
 *   - Other values: Create a new tile of the specified type.
 */
void TileManager::SetTileAt(const float x, const float y, const int tileType) {

    const float tileWidth = TILE_LENGTH * WINDOW_SCALE_FACTOR_X - 6.0f;
    const float tileHeight = TILE_LENGTH * WINDOW_SCALE_FACTOR_Y - 6.0f;

    if (y >= 0 && y < tiles_.size() && x >= 0 && x < tiles_[y].size()) {
        if (tileType == 0) {
            tiles_[y][x] = nullptr;
        } else {
            tiles_[y][x] = std::make_unique<Tile>(
                position_.x + static_cast<float>(x * tileWidth),
                position_.y + static_cast<float>(y * tileHeight),
                TILE_DIRT_TEXTURE);
        }
    } else {
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
