//
// Created by ben on 8/19/24.
//

#ifndef THE_LAND_OF_BOARS_COLLISIONHANDLER_H
#define THE_LAND_OF_BOARS_COLLISIONHANDLER_H

#include <memory>
#include "GameObject.h"

/**
 * @file CollisionHandler.h
 * @brief Provides static methods for handling collisions between game objects.
 *
 * This class serves as a utility for managing interactions between game objects,
 * such as collisions with platforms. Additional collision types can be added as needed.
 */

/**
 * @class CollisionHandler
 * @brief Handles collisions between game objects in the platformer game.
 *
 * This class provides static methods to process specific types of collisions.
 * For example, it includes functionality for detecting and resolving platform collisions.
 */
class CollisionHandler {
public:
    /**
     * @brief Handles collisions between a game object and a platform.
     *
     * This method resolves interactions between a game object (e.g., a player or monster)
     * and a platform. It ensures proper positioning and prevents objects from falling through
     * or overlapping with platforms.
     *
     * @param obj Pointer to the game object involved in the collision.
     * @param platform Pointer to the platform with which the object is colliding.
     */
    static void HandlePlatformCollision(GameObject* obj, GameObject* platform);

    static bool GetCoinCollision(GameObject* player, GameObject* coin);
};

#endif //THE_LAND_OF_BOARS_COLLISIONHANDLER_H
