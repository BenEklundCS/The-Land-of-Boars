//
// Created by ben on 10/8/24.
//

#ifndef THE_LAND_OF_BOARS_BEE_H
#define THE_LAND_OF_BOARS_BEE_H

#include "Monster.h"
#include "../../Sprites/Animation.h"

// **Bee Constants**
#define BEE_MAX_HEALTH 2 ///< The maximum health of the bee.
#define BEE_ATTACK_RANGE 200.0f ///< The attack range of the bee in game units.

/**
 * @file Bee.h
 * @brief Defines the Bee class, representing a bee monster in the game.
 *
 * This class extends the Monster class and implements bee-specific behaviors,
 * including animation, health, attack range, and death handling.
 */

/**
 * @class Bee
 * @brief Represents a bee monster in the game.
 *
 * The Bee class inherits from the Monster class and provides specific functionality for the bee,
 * including its animation, health management, and attack range. It also includes behavior for handling
 * the bee's death and its animation updates.
 */
class Bee : public Monster {
private:
    std::unique_ptr<Animation> beeAnimation_; ///< The animation associated with the bee.

    /**
     * @brief Checks if the bee is within attack range.
     *
     * This method checks whether the bee is within the specified attack range to perform an attack.
     *
     * @return `true` if the bee is within attack range, `false` otherwise.
     */
    bool InAttackRange();

    /**
     * @brief Updates the bee's animation.
     *
     * This method updates the bee's animation to reflect its current state (e.g., idle, flying, attacking).
     */
    void AnimateBee();

public:
    /**
     * @brief Constructs a Bee object with a specified position, dimensions, and state.
     *
     * Initializes the bee's position, dimensions, and state, and sets up the bee's animation.
     *
     * @param posX The x-coordinate of the bee.
     * @param posY The y-coordinate of the bee.
     * @param dimX The width of the bee.
     * @param dimY The height of the bee.
     * @param state The initial state of the bee.
     */
    Bee(float posX, float posY, float dimX, float dimY, MonsterState state);

    /**
     * @brief Draws the bee on the screen.
     *
     * This method overrides the base class's Draw method to render the bee using its current animation.
     */
    void Draw() override;

    /**
     * @brief Updates the bee’s state.
     *
     * This method overrides the base class's Update method and manages the bee's behavior,
     * such as moving, attacking, and playing its animation.
     */
    void Update() override;

    /**
     * @brief Handles when the bee is hit by the player or another object.
     *
     * This method overrides the base class's HitMonster method, reducing the bee's health
     * based on the damage taken.
     *
     * @param damage The amount of damage inflicted on the bee.
     */
    void HitMonster(int damage) override;

    /**
     * @brief Begins the bee's death animation.
     *
     * This method starts the animation sequence that plays when the bee dies.
     */
    void BeginDeathAnimation();
};

#endif //THE_LAND_OF_BOARS_BEE_H
