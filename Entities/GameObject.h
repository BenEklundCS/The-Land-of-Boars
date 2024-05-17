//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_GAMEOBJECT_H
#define PLATFORMER_GAMEOBJECT_H


class GameObject {
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual ~GameObject();
};

#endif //PLATFORMER_GAMEOBJECT_H
