//
// Created by ben on 5/30/24.
//

#include "../../../include/Game/Management/TileManager.h"
#include "../../../include/Platform/Globals.h"

// Create tiles creates a tilemap given a 2d vector of integers
// - 0 for GRASS
// - 1 for DIRT
// - 2 for EMPTY (nullptr)
void TileManager::CreateTiles(const std::vector<std::vector<int>> tileMap) {
    // Resize tiles_ to match the size of tileMap
    tiles_.resize(tileMap.size());

    for (int i = 0; i < tileMap.size(); ++i) {
        tiles_[i].resize(tileMap[i].size());
    }

    int tile_overlap = 6;

    for (int i = 0; i < tileMap.size(); ++i) {
        for (int j = 0; j < tileMap[i].size(); ++j) {
            switch (tileMap[i][j]) {
                case 0:
                    tiles_[i][j] = nullptr;
                    break;
                case 1:
                    tiles_[i][j] = std::make_unique<Tile>(position_.x + (float)(j * (TILE_LENGTH - tile_overlap)),
                                                          position_.y + (float)(i * (TILE_LENGTH - tile_overlap)), TILE_DIRT_TEXTURE);
                    break;
                case 2:
                    tiles_[i][j] = std::make_unique<Tile>(position_.x + (float)(j * (TILE_LENGTH - tile_overlap)),
                                                          position_.y + (float)(i * (TILE_LENGTH - tile_overlap)), TILE_GRASS_TEXTURE);
                    break;
            }
        }
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
