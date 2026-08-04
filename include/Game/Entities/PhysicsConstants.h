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
 * All values are in fixed **world units per second** and are deliberately NOT
 * scaled by the window size - resolution is handled by the camera's zoom.
 * Scaling these by the window factor (as an earlier version did) made gravity
 * and friction depend on the aspect ratio, so the game played differently in a
 * different-shaped window.
 */

/**
 * @brief The gravitational constant for the game world, in world units.
 */
#define GRAVITY 45.0f

/**
 * @brief The friction constant for decelerating entities, in world units.
 */
#define FRICTION 85.0f

/**
 * @brief The maximum velocity for entities, in world units.
 *
 * Prevents entities reaching excessive speeds.
 */
#define MAX_VELOCITY 1000.0f

#endif //PLATFORMER_PHYSICSCONSTANTS_H
