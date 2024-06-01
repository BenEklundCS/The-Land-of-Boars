//
// Created by ben on 5/30/24.
//

#include "../../../include/Game/Management/TileManager.h"

void TileManager::Draw() {
    for (auto& tile_vector : tiles_) {
        for (auto& tile : tile_vector) {
            if (tile != nullptr) {
                tile->Draw();
            }
        }
    }
}

void TileManager::Update() {}

void TileManager::CreateTiles(const std::vector<std::vector<int>> tileMap) {
    // Resize tiles_ to match the size of tileMap
    tiles_.resize(tileMap.size());
    for (int i = 0; i < tileMap.size(); ++i) {
        tiles_[i].resize(tileMap[i].size());
    }

    for (int i = 0; i < tileMap.size(); ++i) {
        for (int j = 0; j < tileMap[i].size(); ++j) {
            switch (tileMap[i][j]) {
                case 0:
                    tiles_[i][j] = std::make_unique<Tile>(position_.x + j * 100, position_.y + i * 100, TILE_GRASS_TEXTURE);
                    break;
                case 1:
                    tiles_[i][j] = std::make_unique<Tile>(position_.x + j * 100, position_.y + i * 100, TILE_DIRT_TEXTURE);
                    break;
                case 2:
                    tiles_[i][j] = nullptr; // empty space/no tile
                    break;
            }
        }
    }
}

TileManager::TileManager(Vector2 position) {
    this->position_ = position;
}
