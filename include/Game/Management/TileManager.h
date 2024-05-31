//
// Created by ben on 5/30/24.
//

#ifndef PLATFORMER_TILEMANAGER_H
#define PLATFORMER_TILEMANAGER_H


#include <vector>
#include "../Entities/Objects/Tile.h"

class TileManager : public GameObject {
private:
    std::vector<Tile> tiles_;
public:

};


#endif //PLATFORMER_TILEMANAGER_H
