//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#define PLAYER_LENGTH 150
#define PLAYER_SPEED 200
#define MAX_JUMPS 1
#define PLAYER_MAX_HP 3

#include <memory>
#include "raylib.h"
#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"
#include "../../Sprites/Animation.h"
#include "../PhysicsConstants.h"

enum PlayerState {
    IDLE,
    RUNNING,
    JUMPING
};

class Player : public GameObject {
private:
    // Methods
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
    [[nodiscard]] bool CheckPlayerDeath() const;
    // Attributes
    Vector2 velocity_{0, 15};
    Animation playerAnimation_;
    PlayerState state_;
    PlayerState last_state_;
    bool movingRight_;
    int jumps_ = 0;
    int hp_ = PLAYER_MAX_HP;
public:
    GameObjectType type_;
    Player();
    void Update() override;
    void Draw() override;
    void PlatformCollision(GameObject* obj);
    void AnimatePlayer();
    void HitPlayer();
};

#endif //PLATFORMER_PLAYER_H
