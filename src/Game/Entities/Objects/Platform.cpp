//
// Created by ben on 5/17/24.
//



#include "../../../../include/Game/Entities/Objects/Platform.h"

// Constructor for the platform
Platform::Platform(const float pos_x, const float pos_y, const float dim_x, const float dim_y, const Color color) : GameObject(PLATFORM) {
    this->position_ = Vector2{pos_x, pos_y};
    this->dimensions_ = Vector2{dim_x, dim_y};
    // Scale the game object
    Scale();
    this->color_ = color;
}

// Draw call is just a raylib DrawRect call
void Platform::Draw() {
    DrawRectangleRec(GetRect(), color_);
}

// Platforms are stationary so this method can be empty
void Platform::Update() {

}
