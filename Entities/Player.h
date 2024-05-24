//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#define PLAYER_LENGTH 150
#define PLAYER_SPEED 200
#define MAX_VELOCITY 50
#define GRAVITY 45
#define FRICTION 85
#define MAX_JUMPS 1

#include <memory>
#include "raylib.h"
#include "GameObject.h"
#include "../Sprites/TextureManager.h"
#include "../Sprites/Animation.h"

enum PlayerState {
    IDLE,
    RUNNING,
    JUMPING
};

class Player : public GameObject {
private:
    Vector2 velocity_{0, 15};
    void MovePlayer(float deltaTime);
    void UpdatePosition();
    void ApplyFriction(float deltaTime);
    void ApplyGravity(float deltaTime);
    void HandlePlayerInput(float deltaTime);
    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);
    void Jump(float deltaTime);
    void ResetJumps();
    void VelocityBound();
    Animation playerAnimation_;
    PlayerState state_;
    PlayerState last_state_;
    bool movingRight_;
    int jumps_ = 0;
    float timeSinceCollision = 0.0f;
public:
    Player();
    void Update() override;
    void Draw() override;
    void PlatformCollision(GameObject* obj);
    void AnimatePlayer();
};

#endif //PLATFORMER_PLAYER_H
