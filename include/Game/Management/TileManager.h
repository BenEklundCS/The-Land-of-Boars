//
// Created by ben on 5/30/24.
//

#ifndef PLATFORMER_TILEMANAGER_H
#define PLATFORMER_TILEMANAGER_H


#include <vector>
#include "../Entities/Objects/Tile.h"

// The TileManager is a drawable GameObject, simplifying the management of its tiles
class TileManager : public GameObject {
private:
    std::vector<std::unique_ptr<Tile>> tiles_;
public:
     void Draw() override;
};


#endif //PLATFORMER_TILEMANAGER_H
