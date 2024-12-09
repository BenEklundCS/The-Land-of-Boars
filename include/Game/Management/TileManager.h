//
// Created by ben on 5/30/24.
//

#ifndef PLATFORMER_TILEMANAGER_H
#define PLATFORMER_TILEMANAGER_H


#include <vector>
#include "../Entities/Objects/Tile.h"

// The TileManager class manages and creates tiles from a 2D array of integers
// simplifying the creation of tiles!
class TileManager {
private:
    Vector2 position_{};
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles_;
public:
    explicit TileManager(Vector2 position);
    void CreateTiles(std::vector<std::vector<int>> tileMap_);
    std::vector<std::vector<std::unique_ptr<Tile>>> GetTiles();
    [[nodiscard]] std::unique_ptr<Tile> GetTileAt(float x, float y) const;
    void SetTileAt(float x, float y, int tile);
};


#endif //PLATFORMER_TILEMANAGER_H
