//
// Created by ben on 5/17/24.
//



#include "../../../../include/Game/Entities/Objects/Platform.h"

/**
 * @brief Constructs a Platform object.
 *
 * Initializes the platform's position, dimensions, and color. The platform is scaled
 * based on the window scale factor during construction.
 *
 * @param pos_x The X-coordinate of the platform's position.
 * @param pos_y The Y-coordinate of the platform's position.
 * @param dim_x The width of the platform.
 * @param dim_y The height of the platform.
 * @param color The color of the platform (used for rendering).
 */
Platform::Platform(const float pos_x, const float pos_y, const float dim_x, const float dim_y, const Color color) : GameObject(PLATFORM) {
    this->position_ = Vector2{pos_x, pos_y};
    this->dimensions_ = Vector2{dim_x, dim_y};
    // Scale the game object
    Scale();
    this->color_ = color;
}

/**
 * @brief Draws the platform on the screen.
 *
 * Uses the Raylib `DrawRectangleRec` function to render the platform as a rectangle.
 */
void Platform::Draw() {
    DrawRectangleRec(GetRect(), color_);
}

/**
 * @brief Updates the platform.
 *
 * Platforms are stationary and do not require update logic. This method is included
 * to adhere to the GameObject interface.
 */
void Platform::Update() {

}
