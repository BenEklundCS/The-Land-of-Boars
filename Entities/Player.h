//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#define PLAYER_LENGTH 50
#define GRAVITY 45

#include "raylib.h"
#include "GameObject.h"

class Player : public GameObject {
private:
    Vector2 velocity_{0, 15};
    Color color_{};
    void MovePlayer();
public:
    Player();
    void Update() override;
    void Draw() override;
    Color GetColor();
    void HandlePlayerInput();
    Vector2 GetVelocity();
    void SetVelocity(Vector2 velocity);
};

#endif //PLATFORMER_PLAYER_H
