//
// Created by ben on 5/17/24.
//

#include "Platform.h"

Platform::Platform(float pos_x, float pos_y, float dim_x, float dim_y, Color color) {
    this->position_ = Vector2{pos_x, pos_y};
    this->dimensions_ = Vector2{dim_x, dim_y};
    this->color_ = color;
    this->type_ = ObjectType::PLATFORM;
}

void Platform::Draw() {
    DrawRectangleRec(GetRect(), color_);
}

void Platform::Update() {

}
