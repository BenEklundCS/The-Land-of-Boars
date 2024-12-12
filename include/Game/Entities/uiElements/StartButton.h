//
// Created by ben on 12/12/24.
//

#ifndef THE_LAND_OF_BOARS_STARTBUTTON_H
#define THE_LAND_OF_BOARS_STARTBUTTON_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"

class StartButton : public GameObject {
private:
    GameTexture gameTexture_{};
public:
    StartButton(float pos_x, float pos_y);
    void Update() override;
    void Draw() override;
};

#endif //THE_LAND_OF_BOARS_STARTBUTTON_H
