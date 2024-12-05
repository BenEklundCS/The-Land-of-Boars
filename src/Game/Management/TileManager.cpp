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

std::unique_ptr<Tile> TileManager::GetTileAt(float x, float y) const {
    int tile_overlap = 6;
    int tileX = static_cast<int>((x - position_.x) / (TILE_LENGTH - tile_overlap));
    int tileY = static_cast<int>((y - position_.y) / (TILE_LENGTH - tile_overlap));

    if (tileX >= 0 && tileX < tiles_.size() && tileY >= 0 && tileY < tiles_[tileX].size()) {
        return std::make_unique<Tile>(*tiles_[tileX][tileY]);
    }
    return nullptr;
}

void TileManager::SetTileAt(const float x, const float y, const int tile) {
    constexpr int tile_overlap = 6;
    int tileX = static_cast<int>((x - position_.x) / (TILE_LENGTH - tile_overlap));
    int tileY = static_cast<int>((y - position_.y) / (TILE_LENGTH - tile_overlap));

    // Debug logs
    TraceLog(LOG_DEBUG, "SetTileAt: Mouse (%f, %f) -> Indices (%d, %d)", x, y, tileX, tileY);

    // Check bounds
    if (tileY >= 0 && tileY < tiles_.size() && tileX >= 0 && tileX < tiles_[tileY].size()) {
        switch (tile) {
            case 0:
                tiles_[tileY][tileX] = nullptr;
            break;
            case 1:
                tiles_[tileY][tileX] = std::make_unique<Tile>(
                    position_.x + static_cast<float>(tileX * (TILE_LENGTH - tile_overlap)),
                    position_.y + static_cast<float>(tileY * (TILE_LENGTH - tile_overlap)), TILE_DIRT_TEXTURE);
            break;
            case 2:
                tiles_[tileY][tileX] = std::make_unique<Tile>(
                    position_.x + static_cast<float>(tileX * (TILE_LENGTH - tile_overlap)),
                    position_.y + static_cast<float>(tileY * (TILE_LENGTH - tile_overlap)), TILE_GRASS_TEXTURE);
            break;
            default:
                TraceLog(LOG_FATAL, "Unknown tile type passed to SetTileAt");
        }
    } else {
        TraceLog(LOG_ERROR, "SetTileAt: Out-of-bounds indices (%d, %d). tiles_ size: rows: %zu, cols: %zu",
                 tileY, tileX, tiles_.size(), tiles_.empty() ? 0 : tiles_[0].size());
    }
}



// GetTiles returns a flattened Vector representing the tile objects
// Handles the nullptrs and does not return them to the outside
std::vector<std::unique_ptr<Tile>> TileManager::GetTiles() {
    std::vector<std::unique_ptr<Tile>> tiles;
    for (auto & tile_vector : tiles_)
        for (auto & tile : tile_vector)
            if (tile != nullptr)
                tiles.push_back(std::move(tile));
    return tiles;
}

// Constructor
TileManager::TileManager(Vector2 position) {
    this->position_ = position;
}
