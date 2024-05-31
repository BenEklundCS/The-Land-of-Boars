//
// Created by ben on 5/30/24.
//

#include "../../../include/Game/Management/TileManager.h"

void TileManager::Draw() {
    for (auto& tile : tiles_) {
        tile->Draw();
    }
}
