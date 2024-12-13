//
// Created by ben on 5/26/24.
//

#ifndef PLATFORMER_PHYSICSCONSTANTS_H
#define PLATFORMER_PHYSICSCONSTANTS_H

#include "../../../include/Platform/Globals.h"

/**
 * @file PhysicsConstants.h
 * @brief Defines physical constants for the game physics system.
 *
 * These constants determine gravity, friction, and maximum velocity
 * in the game world. All values are dynamically scaled according
 * to the screen resolution, ensuring consistent gameplay experience
 * across different display sizes.
 */

/**
 * @brief The gravitational constant for the game world.
 *
 * This value simulates the effect of gravity on entities
 * in the game and is scaled by the vertical window scaling factor
 * (`WINDOW_SCALE_FACTOR_Y`) to maintain consistent behavior on
 * different screen resolutions.
 */
#define GRAVITY (45.0f * WINDOW_SCALE_FACTOR_Y)

/**
 * @brief The friction constant for decelerating entities.
 *
 * This value simulates frictional forces applied to moving entities
 * and is scaled by the horizontal window scaling factor
 * (`WINDOW_SCALE_FACTOR_X`) to ensure consistency across resolutions.
 */
#define FRICTION (85.0f * WINDOW_SCALE_FACTOR_X)

/**
 * @brief The maximum velocity constant for entities.
 *
 * This value defines the maximum speed that entities (such as players
 * or monsters) can reach, ensuring balance and preventing excessively
 * high speeds. The value is scaled by the horizontal window scaling
 * factor (`WINDOW_SCALE_FACTOR_X`).
 */
#define MAX_VELOCITY (1000.0f * WINDOW_SCALE_FACTOR_X)

#endif //PLATFORMER_PHYSICSCONSTANTS_H
