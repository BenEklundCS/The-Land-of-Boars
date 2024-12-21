//
// Created by luke4 on 11/25/2024.
//

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"

class PlayerUI : public GameObject {
private:
    GameTexture gameTexture_{};
    int hp_;
    int coins_;
public:
    PlayerUI(float pos_x, float pos_y, int hp, int coins);
    void Update() override;
    void Draw() override;
};

#endif //HEALTHBAR_H
