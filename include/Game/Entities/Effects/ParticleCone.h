//
// Created by ben on 8/17/24.
//

#ifndef THE_LAND_OF_BOARS_EFFECT_H
#define THE_LAND_OF_BOARS_EFFECT_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"
#include "../../Sprites/Animation.h"

/**
 * @file Effect.h
 * @brief Defines the ParticleCone class, representing a particle effect in the game.
 *
 * This class creates and handles a particle cone effect that is emitted from the player in a specific direction.
 * It handles the particle behavior, including drawing, updating, and determining when to remove the effect.
 */

/**
 * @class ParticleCone
 * @brief Represents a particle cone effect in the game.
 *
 * The ParticleCone class is responsible for creating a visual particle effect that is emitted from the player
 * character in a specific direction. The particles are rendered and updated based on the player's facing direction.
 */
class ParticleCone : public GameObject {
public:
    /**
     * @brief Constructs a ParticleCone object with a specific position, player dimensions, and facing direction.
     *
     * Initializes the particle cone effect, determining the number of particles, direction, and initial position.
     *
     * @param position The initial position of the particle cone.
     * @param playerDimensions The dimensions of the player to calculate particle emission area.
     * @param facingRight A flag indicating whether the player is facing right (particles emit accordingly).
     * @param particleCount The number of particles to generate for the effect.
     */
    ParticleCone(Vector2 position, Vector2 playerDimensions, bool facingRight, float particleCount);

    /**
     * @brief Updates the particle cone effect.
     *
     * This method overrides the base class's Update method to update the behavior of the particles,
     * including their movement and lifespan.
     */
    void Update() override;

    /**
     * @brief Draws the particle cone effect on the screen.
     *
     * This method overrides the base class's Draw method to render the particles of the cone effect.
     */
    void Draw() override;

    /**
     * @brief Checks if the particle cone effect should be removed.
     *
     * This method checks if the particle effect has finished and should be removed from the game world.
     *
     * @return `true` if the effect should be removed, `false` otherwise.
     */
    bool ShouldRemove() const;

private:
    bool facingRight_; ///< Indicates whether the particle cone is facing right.
    float particleCount_; ///< The number of particles to be emitted in the cone.
    bool shouldRemove_ = false; ///< Flag to indicate whether the particle cone should be removed.
    Vector2 playerDimensions_{}; ///< The player's dimensions, used to calculate the emission area.
    Vector2 position_{}; ///< The position of the particle cone effect.
};

#endif //THE_LAND_OF_BOARS_EFFECT_H
