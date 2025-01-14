//
// Created by ben on 12/12/24.
//

#ifndef THE_LAND_OF_BOARS_BUTTON_H
#define THE_LAND_OF_BOARS_BUTTON_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"

#define BUTTON_WIDTH 240
#define BUTTON_HEIGHT 120

class Button : public GameObject {
private:
    GameTexture texture_{};
    std::string text;
public:
    Button(float pos_x, float pos_y, const std::string& text);
    void Update() override;
    void Draw() override;
};

#endif //THE_LAND_OF_BOARS_BUTTON_H
