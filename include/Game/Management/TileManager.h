//
// Created by ben on 5/30/24.
//

#ifndef PLATFORMER_TILEMANAGER_H
#define PLATFORMER_TILEMANAGER_H


#include <vector>
#include "../Entities/Objects/Tile.h"

// The TileManager is a drawable GameObject, simplifying the management of its tiles
class TileManager {
private:
    Vector2 position_{};
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles_;
public:
    TileManager(Vector2 position);
    void CreateTiles(std::vector<std::vector<int>> tileMap_);
    std::vector<std::unique_ptr<Tile>> GetTiles();
};


#endif //PLATFORMER_TILEMANAGER_H
