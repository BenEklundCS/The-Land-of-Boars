//
// Created by ben on 5/17/24.
//

#include "GameObject.h"

GameObject::~GameObject() = default;

Rectangle GameObject::GetRect() {
    return Rectangle{position_.x, position_.y, dimensions_.x, dimensions_.y};
}

// Each object has its own player collision logic
void GameObject::CollideWithPlayer(Player *player) {

}

GameObject::GameObject(GameObjectType type) {
    type_ = type;
}
