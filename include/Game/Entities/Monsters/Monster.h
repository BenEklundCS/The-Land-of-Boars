//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_MONSTER_H
#define PLATFORMER_MONSTER_H

#include "../GameObject.h"
#include "../Player/Player.h"

// **Monster Constants**
#define PACING_WINDOW (800 * WINDOW_SCALE_FACTOR_X) ///< The horizontal range for the monster's pacing.
#define MONSTER_SPEED (3 * WINDOW_SCALE_FACTOR_X) ///< The speed at which the monster moves.

/// **MonsterState Enumeration**
/// Defines the various states that a monster can be in during gameplay.
enum MonsterState {
    PACING,          ///< The monster is pacing back and forth.
    MOVE_TO_GROUNDED, ///< The monster is moving towards a grounded state.
    MOVE_TO_FLYING,   ///< The monster is moving towards a flying state.
    DYING,           ///< The monster is in the dying state.
    DEFAULT          ///< The default state of the monster.
};

/**
 * @file Monster.h
 * @brief Defines the Monster class, representing the base class for all monsters in the game.
 *
 * This class serves as a base for various monster types, encapsulating functionality like movement,
 * health, state management, and collision handling with the player.
 */

/**
 * @class Monster
 * @brief Represents a monster in the platformer game.
 *
 * The Monster class inherits from `GameObject` and `Subject`. It provides the basic functionality
 * for managing a monster's state, health, movement, and interactions with the player. It can be extended
 * by specific monster types for more specialized behavior.
 */
class Monster : public GameObject, public Subject {
private:
    Vector2 initialPosition_{}; ///< The monster's initial position when it is created.

protected:
    int hp_; ///< The health of the monster.
    MonsterState state_; ///< The current state of the monster.

public:
    GameObjectType type_ = MONSTER; ///< The type of the object (MONSTER).

    /**
     * @brief Constructs a Monster object with a specified position, dimensions, and state.
     *
     * Initializes the monster's position, dimensions, health, and state.
     *
     * @param pos_x The x-coordinate of the monster's position.
     * @param pos_y The y-coordinate of the monster's position.
     * @param dim_x The width of the monster.
     * @param dim_y The height of the monster.
     * @param state The initial state of the monster.
     */
    Monster(float pos_x, float pos_y, float dim_x, float dim_y, MonsterState state);

    /**
     * @brief Draws the monster on the screen.
     *
     * This method overrides the base class's Draw method to render the monster at its current position.
     */
    void Draw() override;

    /**
     * @brief Updates the monster's state for the current frame.
     *
     * This method overrides the base class's Update method to handle the monster's state updates,
     * movement, and behavior.
     */
    void Update() override;

    /**
     * @brief Moves the monster according to its velocity.
     *
     * This method updates the monster's position based on its current velocity.
     */
    void MoveMonster();

    /**
     * @brief Handles collision detection with the player.
     *
     * This method checks if the monster collides with the player and handles the interaction accordingly.
     *
     * @param player The player object that the monster may collide with.
     */
    void CollideWithPlayer(Player* player) override;

    /**
     * @brief Retrieves the current health of the monster.
     *
     * @return The current health of the monster.
     */
    [[nodiscard]] int GetHealth() const;

    /**
     * @brief Sets the health of the monster.
     *
     * @param hp The new health value for the monster.
     */
    void SetHealth(int hp);

    /**
     * @brief Handles damage taken by the monster.
     *
     * This virtual method allows specific monsters to implement custom behavior when they take damage.
     *
     * @param damage The amount of damage taken by the monster.
     */
    virtual void HitMonster(int damage);

    /**
     * @brief Moves the monster based on its default movement behavior.
     *
     * This method allows the monster to move according to its default movement pattern (e.g., pacing).
     */
    void MoveDefault();

    /**
    * @brief Marks the monster for removal after death and spawns coins.
    */
    void Died();

    /**
    * @brief Drops coins from the monster by adding them to the scene. Called on-death to reward the player.
    */
    void DropCoins();
};

#endif //PLATFORMER_MONSTER_H
