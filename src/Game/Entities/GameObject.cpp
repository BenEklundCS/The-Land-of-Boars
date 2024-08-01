//
// Created by ben on 5/17/24.
//

#include "../../../include/Game/Entities/GameObject.h"

// Construct a GameObject using the type
GameObject::GameObject(GameObjectType type)
        : type_(type), position_{0.0f, 0.0f}, dimensions_{0.0f, 0.0f} {
}

GameObject::~GameObject() = default;

// Returns the Rectangle defined by the GameObjects current position x/y and dimensions x/y
Rectangle GameObject::GetRect() {
    return Rectangle{position_.x, position_.y, dimensions_.x, dimensions_.y};
}

// Each object has its own player collision logic and can override this method
void GameObject::CollideWithPlayer(Player *player) {

}

void GameObject::ToggleFlashing() {
    if (!hasBeenToggled_) {
        hasBeenToggled_ = true;
        timeSinceToggle_ = 0.0f;
        color_ = RED;
    }
}

// Update player flashing behavior
void GameObject::UpdateFlashing(float deltaTime) {
    timeSinceToggle_ += deltaTime;
    timeStepForFlash_ += deltaTime;

    if (hasBeenToggled_) {

        if (timeStepForFlash_ > 0.2f) {
            flashToggle_ = !(bool)flashToggle_;
            if (!flashToggle_) {
                color_ = RED;
            } else {
                color_ = WHITE;
            }
            timeStepForFlash_ = 0.0f;
        }

        if (timeSinceToggle_ > 1.0f) {
            hasBeenToggled_ = false;
            color_ = WHITE;
        }
    }
}

// Returns the current position of the object
Vector2 GameObject::GetPosition() {
    return position_;
}


