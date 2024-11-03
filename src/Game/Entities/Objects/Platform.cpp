//
// Created by ben on 5/17/24.
//



#include "../../../../include/Game/Entities/Objects/Platform.h"

// Constructor for the platform
Platform::Platform(float pos_x, float pos_y, float dim_x, float dim_y, Color color) : GameObject(PLATFORM) {
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
