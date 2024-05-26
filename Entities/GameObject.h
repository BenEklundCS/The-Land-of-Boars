//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_GAMEOBJECT_H
#define PLATFORMER_GAMEOBJECT_H

#include "raylib.h"

class Player; // forward declaration, as Player is an instance of GameObject

enum GameObjectType {
    PLAYER,
    PLATFORM,
    MONSTER,
    OTHER
};

class GameObject {
protected:
    Vector2 position_{};
    Vector2 dimensions_{};
public:
    GameObjectType type_;
    GameObject(GameObjectType type = OTHER);
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void CollideWithPlayer(Player* player);
    Vector2 GetDimensions();
    Vector2 GetPosition();
    Rectangle GetRect();
    virtual ~GameObject();
};

#endif //PLATFORMER_GAMEOBJECT_H
