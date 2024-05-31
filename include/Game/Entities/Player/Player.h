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
#include "../PhysicsConstants.h"
#include "../../Sprites/Animation.h"

// Definitions for PlayerState types
enum PlayerState {
    IDLE,
    RUNNING,
    JUMPING
};

// Player is a GameObject with all player logic encapsulated
class Player : public GameObject {
private:
    // Methods
    void MovePlayer(float deltaTime); // Move the player for the current frame
    void UpdatePosition(); // Update the player position based on its velocity
    void ApplyFriction(float deltaTime); // Friction
    void ApplyGravity(float deltaTime); // Gravity
    void HandlePlayerInput(float deltaTime); // Input handling
    void MoveLeft(float deltaTime); // Move the player to the left
    void MoveRight(float deltaTime); // Move the player to the right
    void Jump(float deltaTime); // Jump (with double jump!)
    void ResetJumps(); // Reset the player jump counter
    void VelocityBound(); // Prevent the players velocity from increasing past the bound
    [[nodiscard]] bool CheckPlayerDeath() const; // Check if the player is dead
    // Attributes
    Vector2 velocity_{0, 15}; // Player velocity vector
    Animation playerAnimation_; // Player animation
    PlayerState state_; // Player state
    PlayerState last_state_; // Previous player state
    bool movingRight_; // Flag to check x direction
    int jumps_ = 0; // Jump counter used to check if we can jump
    int hp_ = PLAYER_MAX_HP; // Current player hp
public:
    GameObjectType type_ = PLAYER;
    Player();
    void Update() override; // Update the player for the current frame
    void Draw() override; // Draw the player
    void PlatformCollision(GameObject* obj); // Handle a collision with a platform GameObject
    void AnimatePlayer(); // Animate the player
    void HitPlayer();
};

#endif //PLATFORMER_PLAYER_H
