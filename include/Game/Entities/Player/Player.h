//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_PLAYER_H
#define PLATFORMER_PLAYER_H

#include <cmath>
#include <memory>
#include "raylib.h"
#include "../GameObject.h"
#include "../PhysicsConstants.h"
#include "../../Sprites/Animation.h"
#include "../../Sprites/TextureManager.h"
#include "../../Events/Observers/Subject.h"
#include "../uiElements/PlayerUI.h"

/// **Player Constants**
/// These constants define the player's movement, physics, and other gameplay attributes.
#define PLAYER_SPEED_X (200.0f * WINDOW_SCALE_FACTOR_X)
#define PLAYER_SPEED_Y (200.0f * WINDOW_SCALE_FACTOR_Y)
#define PLAYER_JUMP_HEIGHT (INVERSE_WINDOW_SCALE_FACTOR_Y)
#define PLAYER_JUMP_POWER (sqrt(2 * GRAVITY * PLAYER_JUMP_HEIGHT))
#define PLAYER_MAX_JUMPS 1
#define PLAYER_MAX_HP 7
#define PLAYER_LENGTH 150 ///< Length of the player; scaling handled internally.
#define PLAYER_ATTACK_DELAY 0.5f ///< Delay between player attacks in seconds.

/// **Player State Enumeration**
/// Defines the various states the player can be in during gameplay.
enum PlayerState {
    IDLE,      ///< Player is idle.
    RUNNING,   ///< Player is running.
    JUMPING,   ///< Player is jumping.
    ATTACKING  ///< Player is attacking.
};

/// **Player Data Structure**
/// Encapsulates the player's attributes, animations, and state data.
struct playerDataStruct {
    // **General Properties**
    int hp_ = PLAYER_MAX_HP; ///< Current player health.
    int damage_ = 1;         ///< Damage dealt by the player.
    int coins_ = 0;

    // **Animation**
    float timeSinceHit_ = 0.0f; ///< Time since the player was last hit.
    float timeSinceLastAttack_ = 0.0f; ///< Time since the last attack.
    std::unique_ptr<Animation> playerAnimation_; ///< Current player animation.
    PlayerState state_ = IDLE; ///< Current state of the player.
    PlayerState last_state_ = IDLE; ///< Previous state of the player.

    // **Movement**
    int jumps_ = 0; ///< Number of jumps performed (e.g., for double jump logic).
    bool isOnGround_ = false; ///< Indicates if the player is on the ground.
    float attackRange_ = 500.0f * WINDOW_SCALE_FACTOR_X; ///< Attack range.
};

/// **Player Class**
/// A specialized GameObject that encapsulates all player logic and behavior.
/// Inherits from `GameObject` and `Subject` (for observer pattern support).
class Player : public GameObject, public Subject {
private:
    // **Attributes**
    playerDataStruct playerData; ///< Player data structure containing state and attributes.
    std::unique_ptr<PlayerUI> playerUI_; ///< PlayerUI element.

    // **Movement Methods**
    void MovePlayer(float deltaTime); ///< Handles player movement for the current frame.
    void UpdatePosition(float deltaTime); ///< Updates player position based on velocity.

    // **State and Animation**
    [[nodiscard]] bool CheckPlayerDeath() const; ///< Checks if the player is dead.
    void ResetJumps(); ///< Resets the player's jump counter.
    void AnimatePlayer(); ///< Updates the player's animation.
    bool AlreadyAttacking(); ///< Checks if the player is already attacking.
    void LoadNewAnimation(); ///< Loads a new animation based on the player's state.
    void StateTransition(); ///< Handles state transitions (e.g., IDLE to RUNNING).

    // **Utility**
    [[nodiscard]] bool ZeroVelocity() const; ///< Checks if the player's velocity is zero.

public:
    // **Attributes**
    GameObjectType type_ = PLAYER; ///< Type identifier for the player object.

    // **Constructor**
    Player();

    // **Update and Draw**
    void Update() override; ///< Updates the player for the current frame.
    void Draw() override; ///< Draws the player.

    // **Movement**
    void MoveLeft(); ///< Moves the player to the left.
    void MoveRight(); ///< Moves the player to the right.
    void Jump(); ///< Makes the player jump.

    // **Actions**
    void Attack(); ///< Initiates an attack.
    void HitPlayer(); ///< Handles logic when the player is hit.

    // **Accessors**
    [[nodiscard]] bool CanJump() const; ///< Checks if the player can jump.
    playerDataStruct* GetPlayerData(); ///< Returns a pointer to the player's data structure.
};

#endif //PLATFORMER_PLAYER_H
