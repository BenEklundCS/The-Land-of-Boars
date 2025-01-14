//
// Created by ben on 12/12/24.
//

#include <functional>
#include "../../../include/Game/Entities/UI/Button.h"
#include "raylib.h"

Button::Button(Vector2 position, Vector2 dimensions, const std::function<void()>& callback, const std::string& text)
: texture_(TextureManager::GetInstance()->GetTexture(BLUE_BUTTON_TEXTURE)) {
    this->position_ = position;
    this->dimensions_ = dimensions;
    this->text_ = text;
    this->onClick_ = callback;
}

void Button::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);
    DrawText(text_.c_str(), position_.x + dimensions_.x / 4, position_.y + dimensions_.y / 3, 20, BLACK);
}

void Button::ChangeState() {
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, GetRect())) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state_ = BUTTON_PRESSED;
        }
        else {
            state_ = BUTTON_HOVER;
        }
    }
    else {
        state_ = BUTTON_IDLE;
    }
}

void Button::HandleAction() {
    // Call the callback function when the button is pressed
    if (state_ == BUTTON_PRESSED)
        onClick_();
}

void Button::Reset() {
    state_ = BUTTON_IDLE;
}

void Button::Update() {
    ChangeState();
    HandleAction();
    Reset();
}