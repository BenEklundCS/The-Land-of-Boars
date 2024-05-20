//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#define PLAYER_LENGTH 200
#define PLAYER_SPEED 200
#define GRAVITY 45
#define FRICTION 85

#include "raylib.h"
#include "GameObject.h"
#include "../Sprites/TextureManager.h"
#include "../Sprites/Animation.h"

enum PLAYER_STATE {
    IDLE,
    RUNNING,
    JUMPING
};

class Player : public GameObject {
private:
    Vector2 velocity_{0, 15};
    Color color_{};
    void MovePlayer();
    Animation playerAnimation_;
    PLAYER_STATE state;
    PLAYER_STATE last_state;
public:
    Player();
    void Update() override;
    void Draw() override;
    void HandlePlayerInput();
    void PlatformCollision(GameObject* obj);
    void AnimatePlayer();
};

#endif //PLATFORMER_PLAYER_H
