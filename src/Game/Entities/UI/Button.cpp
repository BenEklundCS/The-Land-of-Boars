//
// Created by ben on 12/12/24.
//

#include "../../../include/Game/Entities/UI/Button.h"
#include "../../../include/Game/Sprites/TextureManager.h"
#include "raylib.h"

Button::Button(float pos_x, float pos_y, const std::string& text)
: texture_(TextureManager::GetInstance()->GetTexture(BLUE_BUTTON_TEXTURE)) {
    this->position_ = Vector2{pos_x, pos_y};
    this->dimensions_ = Vector2{BUTTON_WIDTH, BUTTON_HEIGHT};
    this->text = text;
}

void Button::Draw() {
    DrawTexturePro(texture_.texture, texture_.rect, GetRect(), Vector2{0, 0}, 0, WHITE);
}

void Button::Update() {

}