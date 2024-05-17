//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_GAMEOBJECT_H
#define PLATFORMER_GAMEOBJECT_H

#include "raylib.h"

class GameObject {
protected:
    Vector2 position_{};
    Vector2 dimensions_{};
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~GameObject();
    Vector2 GetDimensions();
    Vector2 GetPosition();
    [[maybe_unused]] void SetDimensions(Vector2 dimensions);
    [[maybe_unused]] void SetPosition(Vector2 position);
    Rectangle GetRect();
};

#endif //PLATFORMER_GAMEOBJECT_H
