//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#include <cmath>

#define PLAYER_SPEED (200 * WINDOW_SCALE_FACTOR_X)
#define PLAYER_JUMP_HEIGHT ((2.0f - WINDOW_SCALE_FACTOR_Y))
#define PLAYER_JUMP_POWER (sqrt(GRAVITY * PLAYER_JUMP_HEIGHT))
#define PLAYER_MAX_JUMPS 1
#define PLAYER_MAX_HP 3
#define PLAYER_LENGTH 150 // DO NOT SCALE LENGTHS AND POSITIONS, THIS IS HANDLED BY SCALE() AND INHERITENCE FROM GAMEOBJECT
#define PLAYER_ATTACK_DELAY 0.5f

#include <memory>
#include "raylib.h"
#include "../GameObject.h"
#include "../PhysicsConstants.h"
#include "../../Sprites/Animation.h"
#include "../../Sprites/TextureManager.h"
#include "../../Events/Observers/Subject.h"

// Definitions for PlayerState types
enum PlayerState {
    IDLE,
    RUNNING,
    JUMPING,
    ATTACKING
};

struct playerDataStruct {
    // general properties
    int hp_ = PLAYER_MAX_HP; // Current player hp
    int damage_ = 1;

    // animation
    float timeSinceHit_ = 0.0f;
    float timeSinceLastAttack_ = 0.0f;

    std::unique_ptr<Animation> playerAnimation_; // player animation
    PlayerState state_ = IDLE; // Player state
    PlayerState last_state_ = IDLE; // Previous player state

    // movement
    int jumps_ = 0; // Jump counter used to check if we can jump
    bool isOnGround_ = false;
    float attackRange_ = 500.0f * WINDOW_SCALE_FACTOR_X;
};

// Player is a GameObject with all player logic encapsulated
class Player : public GameObject, public Subject {
private:
    // Methods
    // Movement methods
    void MovePlayer(float deltaTime); // Move the player for the current frame
    void UpdatePosition(float deltaTime); // Update the player position based on its velocity
    void ApplyFriction(); // Friction
    void ApplyGravity(); // Gravity
    // Player state
    [[nodiscard]] bool CheckPlayerDeath() const; // Check if the player is dead
    void ResetJumps(); // Reset the player jump counter
    // Attributes
    playerDataStruct playerData;
    void AnimatePlayer(); // Animate the player
    bool AlreadyAttacking(); // check if the player is attacking
    void LoadNewAnimation();
    void StateTransition();
public:
    GameObjectType type_ = PLAYER;
    Player();
    void Update() override; // Update the player for the current frame
    void Draw() override; // Draw the player
    void MoveLeft(); // Move the player to the left
    void MoveRight(); // Move the player to the right
    void Jump(); // Jump (with double jump!)
    void Attack();
    [[nodiscard]] bool CanJump() const; // Check if the player can jump
    playerDataStruct* GetPlayerData();
    void HitPlayer();
    bool ZeroVelocity() const;
};

#endif //PLATFORMER_PLAYER_H
