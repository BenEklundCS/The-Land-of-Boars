//
// Created by ben on 12/12/24.
//

#include <functional>
#include "../../../include/Game/Entities/UI/Button.h"
#include "raylib.h"

/**
 * @brief Constructs a Button object with the specified position, dimensions, text, and callback.
 *
 * @param position The position of the button on the screen as a Vector2.
 * @param dimensions The width and height of the button as a Vector2.
 * @param callback A function to call when the button is clicked.
 * @param text The text to display on the button.
 */
Button::Button(Vector2 position, Vector2 dimensions, const std::function<void()>& callback, const std::string& text)
        : texture_(TextureManager::GetInstance()->GetTexture(BLUE_BUTTON_TEXTURE)) {
    this->position_ = position;
    this->dimensions_ = dimensions;
    this->text_ = text;
    this->onClick_ = callback;
}

/**
 * @brief Renders the button, including its texture and text.
 */
void Button::Draw() {
    // Draw the button texture
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);

    // Draw the button text centered within the button's dimensions
    DrawText(text_.c_str(), position_.x + dimensions_.x / 4, position_.y + dimensions_.y / 3, 20, BLACK);
}

/**
 * @brief Updates the button's state based on mouse input.
 *
 * Determines whether the button is idle, hovered, or pressed,
 * depending on the mouse's position and button press state.
 */
void Button::ChangeState() {
    Vector2 mousePoint = GetMousePosition(); // Get the current mouse position

    // Check if the mouse is over the button's rectangle
    if (CheckCollisionPointRec(mousePoint, GetRect())) {
        // If the left mouse button is pressed, set the button to pressed state
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state_ = BUTTON_PRESSED;
        }
            // Otherwise, set it to hover state
        else {
            state_ = BUTTON_HOVER;
        }
    }
        // If the mouse is not over the button, set it to idle state
    else {
        state_ = BUTTON_IDLE;
    }
}

/**
 * @brief Executes the button's action when it is pressed.
 *
 * Calls the `onClick_` callback function if the button is in the pressed state.
 */
void Button::HandleAction() {
    if (state_ == BUTTON_PRESSED) {
        // Trigger the action associated with the button press
        onClick_();
    }
}

/**
 * @brief Resets the button's state to idle.
 *
 * This ensures the button does not remain in the pressed or hover state
 * after its action is handled.
 */
void Button::Reset() {
    state_ = BUTTON_IDLE;
}

/**
 * @brief Updates the button's logic, including state changes and action handling.
 *
 * This method is called every frame to ensure the button responds to user input.
 * It performs the following steps:
 * - Changes the button's state based on mouse interaction.
 * - Handles the button's action if it is pressed.
 * - Resets the button state after the action is handled.
 */
void Button::Update() {
    ChangeState();
    HandleAction();
    Reset();
}
