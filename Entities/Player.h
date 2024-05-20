//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#define PLAYER_LENGTH 150
#define PLAYER_SPEED 200

#define GRAVITY 45

#define FRICTION 85

#include "raylib.h"
#include "GameObject.h"
#include "../Sprites/TextureManager.h"

class Player : public GameObject {
private:
    Vector2 velocity_{0, 15};
    Color color_{};
    void MovePlayer();
    GameTexture playerTexture_{};
public:
    Player();
    void Update() override;
    void Draw() override;
    void HandlePlayerInput();
    void PlatformCollision(GameObject* obj);
};

enum PLAYER_STATE {
    RUNNING,
    IDLE,
};

#endif //PLATFORMER_PLAYER_H
