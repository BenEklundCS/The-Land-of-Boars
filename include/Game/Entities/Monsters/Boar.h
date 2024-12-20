//
// Created by ben on 5/25/24.
//

#ifndef PLATFORMER_BOAR_H
#define PLATFORMER_BOAR_H

#include "Monster.h"
#include "../../Sprites/Animation.h"

// **Boar Constants**
#define BOAR_MAX_HEALTH 3 ///< The maximum health of the boar.

/**
 * @file Boar.h
 * @brief Defines the Boar class, representing a boar monster in the game.
 *
 * This class extends the Monster class and implements boar-specific behaviors,
 * including animation, death handling, and interactions with the player.
 */

/**
 * @class Boar
 * @brief Represents a boar monster in the game.
 *
 * The Boar class inherits from the Monster class and provides specific functionality for the boar,
 * including its animation, health management, and custom behaviors like oinking and death animations.
 */
class Boar : public Monster {
private:
    std::unique_ptr<Animation> boarAnimation_; ///< The animation associated with the boar.
    float timeSinceLastOink_ = 0.0f; ///< Time passed since the last oink.
    float nextOinkTime_ = 0.0f; ///< The time remaining until the next oink.

    /**
     * @brief Plays an oink sound or triggers behavior.
     *
     * This method is called to perform the oinking action, triggered under certain conditions.
     */
    void MaybeOink();

    /**
     * @brief Updates the boar's animation.
     *
     * This method updates the boar's animation to reflect its current state (e.g., idle, running, etc.).
     */
    void AnimateBoar();

public:
    /**
     * @brief Constructs a Boar object with a specified position, dimensions, and state.
     *
     * Initializes the boar's position, dimensions, and state, and sets up the boar's animation.
     *
     * @param posX The x-coordinate of the boar.
     * @param posY The y-coordinate of the boar.
     * @param dimX The width of the boar.
     * @param dimY The height of the boar.
     * @param state The initial state of the boar.
     */
    Boar(float posX, float posY, float dimX, float dimY, MonsterState state);

    /**
     * @brief Draws the boar on the screen.
     *
     * This method overrides the base class's Draw method to render the boar using its current animation.
     */
    void Draw() override;

    /**
     * @brief Updates the boar’s state.
     *
     * This method overrides the base class's Update method and manages the boar's behavior,
     * such as moving, attacking, and playing its oink animation.
     */
    void Update() override;

    /**
     * @brief Handles when the boar is hit by the player or another object.
     *
     * This method overrides the base class's HitMonster method, reducing the boar's health
     * based on the damage taken.
     *
     * @param damage The amount of damage inflicted on the boar.
     */
    void HitMonster(int damage) override;

    /**
     * @brief Begins the boar's death animation.
     *
     * This method starts the animation sequence that plays when the boar dies.
     */
    void BeginDeathAnimation();
};

#endif //PLATFORMER_BOAR_H
