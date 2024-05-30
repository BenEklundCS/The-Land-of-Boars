//
// Created by ben on 5/17/24.
//

#include "../../include/Entities/GameObject.h"

GameObject::GameObject(GameObjectType type)
        : type_(type), position_{0.0f, 0.0f}, dimensions_{0.0f, 0.0f} {
}

GameObject::~GameObject() = default;

Rectangle GameObject::GetRect() {
    return Rectangle{position_.x, position_.y, dimensions_.x, dimensions_.y};
}

// Each object has its own player collision logic
void GameObject::CollideWithPlayer(Player *player) {

}

Vector2 GameObject::GetPosition() {
    return position_;
}


