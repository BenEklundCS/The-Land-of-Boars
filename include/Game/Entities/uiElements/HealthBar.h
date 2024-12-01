//
// Created by luke4 on 11/25/2024.
//

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"

class HealthBar : public GameObject {
private:
    GameTexture gameTexture_{};
    int hp_;
public:
    HealthBar(float pos_x, float pos_y, int hp);
    void Update() override;
    void Draw() override;
};

#endif //HEALTHBAR_H
