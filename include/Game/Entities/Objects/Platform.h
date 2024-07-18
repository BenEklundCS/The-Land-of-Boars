//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_RECTANGLE_H
#define PLATFORMER_RECTANGLE_H

#include "../GameObject.h"
#include "../Player/Player.h"


class Platform : public GameObject {
// Platform color
protected:
    Color color_{};
public:
    Platform(float pos_x, float pos_y, float dim_x, float dim_y, Color color);
    void Update() override; // Update the platform
    void Draw() override; // Draw the platform
};


#endif //PLATFORMER_RECTANGLE_H
