//
// Created by ben on 5/17/24.
//

#include "raylib.h"
#include "GameObject.h"
#include "../Events/PlayerInput.h"



#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#define PLAYER_LENGTH 100

class Player : public GameObject {
private:
    Vector2 position_{};
    Vector2 dimensions_{};
    Color color_{};
public:
    Player(Vector2 position, Vector2 dimensions, Color color);
    void Update() override;
    void Draw() override;
    void SetPosition(Vector2 position);
    Vector2 GetDimensions();
    Vector2 GetPosition();
    Color GetColor();
};

#endif //PLATFORMER_PLAYER_H
