//
// Created by ben on 5/29/24.
//

#ifndef PLATFORMER_TILE_H
#define PLATFORMER_TILE_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"

class Tile : public GameObject {
private:
    GameTexture texture_;
public:
    Tile(float x, float y, std::string tileTexture);
    void SetTexture(GameTexture texture);
    void Draw() override;
    void Update() override;
};


#endif //PLATFORMER_TILE_H
