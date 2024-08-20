//
// Created by ben on 8/19/24.
//

#ifndef THE_LAND_OF_BOARS_COLLISIONHANDLER_H
#define THE_LAND_OF_BOARS_COLLISIONHANDLER_H

#include "GameObject.h"

class CollisionHandler {
public:
    static void HandlePlatformCollision(GameObject* obj, GameObject* platform);
};

#endif //THE_LAND_OF_BOARS_COLLISIONHANDLER_H
