//
// Created by ben on 5/30/24.
//

#include "../../../include/Game/Management/TileManager.h"
#include "../../../include/Platform/Globals.h"

// Create tiles creates a tilemap given a 2d vector of integers
// - 0 for GRASS
// - 1 for DIRT
// - 2 for EMPTY (nullptr)

// TileManager will need to implement or use a Grid Structure that is easily loadable from .json


void TileManager::CreateTiles(const std::vector<std::vector<int>> tileMap) {
    // Resize tiles_ to match the size of tileMap
    tiles_.resize(tileMap.size());

    for (int i = 0; i < tileMap.size(); ++i) {
        tiles_[i].resize(tileMap[i].size());
    }

    for (int i = 0; i < tileMap.size(); ++i) {
        for (int j = 0; j < tileMap[i].size(); ++j) {
            constexpr int tile_overlap = 6;
            switch (tileMap[i][j]) {
                case 0:
                    tiles_[i][j] = nullptr;
                    break;
                case 1:
                    tiles_[i][j] = std::make_unique<Tile>(position_.x + static_cast<float>(j * (TILE_LENGTH - tile_overlap)),
                                                          position_.y + static_cast<float>(i * (TILE_LENGTH - tile_overlap)), TILE_DIRT_TEXTURE);
                    break;
                case 2:
                    tiles_[i][j] = std::make_unique<Tile>(position_.x + static_cast<float>(j * (TILE_LENGTH - tile_overlap)),
                                                          position_.y + static_cast<float>(i * (TILE_LENGTH - tile_overlap)), TILE_GRASS_TEXTURE);
                    break;
                default:
                    TraceLog(LOG_FATAL, "Unknown tile type was passed to TileManager::CreateTiles()");
            }
        }
    }
}

#include "cmath"

Vector2 TileManager::GetTileAt(float x, float y) const {
    const float tileWidth = TILE_LENGTH * WINDOW_SCALE_FACTOR_X - 6.0f;
    const float tileHeight = TILE_LENGTH * WINDOW_SCALE_FACTOR_Y - 6.0f;

    int tileX = static_cast<int>(std::floor((x - position_.x) / tileWidth));
    int tileY = static_cast<int>(std::floor((y - position_.y) / tileHeight));


    TraceLog(LOG_INFO, "World Position: (%f, %f) -> Indices: (%d, %d)", x, y, tileX, tileY);

    if (tileY >= 0 && tileY < tiles_.size() && tileX >= 0 && tileX < tiles_[tileY].size()) {
        auto tile = tiles_[tileY][tileX].get();
        if (tile) {
            return Vector2{(float)tileX, (float)tileY};
        }
    }
    TraceLog(LOG_WARNING, "Out-of-bounds indices: (%d, %d)", tileX, tileY);
    return {-1, -1}; // not found
}

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



// GetTiles returns a flattened Vector representing the tile objects
// Handles the nullptrs and does not return them to the outside
// Return a const reference to avoid ownership transfer
const std::vector<std::vector<std::unique_ptr<Tile>>>& TileManager::GetTiles() const {
    return tiles_;
}


// Constructor
TileManager::TileManager(Vector2 position) {
    this->position_ = position;
}
