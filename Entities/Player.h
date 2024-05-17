//
// Created by ben on 5/17/24.
//

#include "raylib.h"
#include "GameObject.h"

#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#define PLAYER_LENGTH 100
#define GRAVITY 45

class Player : public GameObject {
private:
    Vector2 position_{};
    Vector2 velocity_{0, 15};
    Vector2 dimensions_{};
    Color color_{};
    void MovePlayer();
public:
    Player();
    void Update() override;
    void Draw() override;
    Vector2 GetDimensions();
    Vector2 GetPosition();
    Color GetColor();
    void HandlePlayerInput();
};

#endif //PLATFORMER_PLAYER_H
