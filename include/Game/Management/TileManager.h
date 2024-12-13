//
// Created by ben on 5/30/24.
//

#ifndef PLATFORMER_TILEMANAGER_H
#define PLATFORMER_TILEMANAGER_H


#include <vector>
#include "../Entities/Objects/Tile.h"

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };
}


// The TileManager class manages and creates tiles from a 2D array of integers
// simplifying the creation of tiles!
#include <unordered_map>

class TileManager {
private:
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles_;
    Vector2 position_{};

public:
    void CreateTiles(const std::vector<std::vector<int>> tileMap);
    Vector2 GetTileAt(float x, float y) const;
    void SetTileAt(const float x, const float y, const int tileType);
    const std::vector<std::vector<std::unique_ptr<Tile>>>& GetTiles() const;
    TileManager(Vector2 position);
};


#endif //PLATFORMER_TILEMANAGER_H
