//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_GAMEOBJECT_H
#define PLATFORMER_GAMEOBJECT_H

enum ObjectType {
    PLAYER,
    MONSTER,
    PLATFORM,
    OBJECT
};

#include "raylib.h"

class GameObject {
protected:
    Vector2 position_{};
    Vector2 dimensions_{};
    ObjectType type_;
public:
    GameObject();
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~GameObject();
    ObjectType GetType();
    Vector2 GetDimensions();
    Vector2 GetPosition();
    Rectangle GetRect();
};

#endif //PLATFORMER_GAMEOBJECT_H
