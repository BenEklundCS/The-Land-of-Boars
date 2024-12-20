//
// Created by ben on 11/1/24.
//

#ifndef THE_LAND_OF_BOARS_SNAIL_H
#define THE_LAND_OF_BOARS_SNAIL_H

#include "Monster.h"
#include "../../Sprites/Animation.h"

#define SNAIL_MAX_HEALTH 2

//
// Created by ben on 11/1/24.
//

#include "Monster.h"
#include "../../Sprites/Animation.h"

/**
 * @file Snail.h
 * @brief Defines the Snail class, which represents a snail monster in the game.
 *
 * This class extends the Monster class and implements functionality for the snail monster,
 * including its health, animations, death behavior, and interactions with the player.
 */

/**
 * @class Snail
 * @brief Represents a snail monster in the game.
 *
 * The Snail class inherits from the Monster class and manages the snail's health, animations,
 * and interactions with the player. It includes behavior for handling death, starting the
 * death animation, and updating the snail’s state.
 */
class Snail : public Monster {
private:
    std::unique_ptr<Animation> snailAnimation_; ///< The animation associated with the snail.

    /**
     * @brief Begins the snail's death animation.
     *
     * This method starts the animation sequence that plays when the snail dies.
     */
    void BeginDeathAnimation();

    /**
     * @brief Updates the snail's animation.
     *
     * This method updates the snail's animation to reflect its current state (e.g., idle, moving, etc.).
     */
    void AnimateSnail();

public:
    /**
     * @brief Constructs a Snail object with a specified position, dimensions, and state.
     *
     * Initializes the snail's position, dimensions, and state, including setting up its animation.
     *
     * @param posX The x-coordinate of the snail.
     * @param posY The y-coordinate of the snail.
     * @param dimX The width of the snail.
     * @param dimY The height of the snail.
     * @param state The initial state of the snail.
     */
    Snail(float posX, float posY, float dimX, float dimY, MonsterState state);

    /**
     * @brief Draws the snail on the screen.
     *
     * This method overrides the base class's Draw method to render the snail using its current animation.
     */
    void Draw() override;

    /**
     * @brief Updates the snail’s state.
     *
     * This method overrides the base class's Update method and manages the snail's behavior,
     * such as moving or changing states.
     */
    void Update() override;

    /**
     * @brief Handles when the snail is hit by the player or another object.
     *
     * This method overrides the base class's HitMonster method and reduces the snail's health
     * based on the damage taken.
     *
     * @param damage The amount of damage inflicted on the snail.
     */
    void HitMonster(int damage) override;
};

#endif //THE_LAND_OF_BOARS_SNAIL_H

