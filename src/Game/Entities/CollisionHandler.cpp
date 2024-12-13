#include "../../../include/Game/Entities/CollisionHandler.h"
#include "cmath"
#include "raylib.h"

/**
 * @brief Handles collisions between a moving object (obj) and a stationary platform.
 *
 * Resolves collisions by determining the direction of the collision and
 * adjusting the object's position and velocity accordingly.
 *
 * - For vertical collisions:
 *   - If the object collides from above the platform, it is placed on top and its vertical velocity is set to zero.
 *   - If the object collides from below, it is placed below the platform and its vertical velocity is set to zero.
 *
 * - For horizontal collisions:
 *   - If the object collides from the left or right of the platform, it is pushed away horizontally, and its horizontal velocity is set to zero.
 *   - If the object is a MONSTER, its direction of movement is toggled.
 *
 * @param obj Pointer to the moving GameObject involved in the collision.
 * @param platform Pointer to the stationary GameObject (platform) involved in the collision.
 */
void CollisionHandler::HandlePlatformCollision(GameObject *obj, GameObject *platform) {
    if (CheckCollisionRecs(obj->GetRect(), platform->GetRect())) {
        auto [obj_x, obj_y, obj_width, obj_height] = obj->GetRect();
        auto [platform_x, platform_y, platform_width, platform_height] = platform->GetRect();

        const float deltaX = (obj_x + obj_width / 2) - (platform_x + platform_width / 2);
        const float deltaY = (obj_y + obj_height / 2) - (platform_y + platform_height / 2);

        float combinedHalfWidths = (obj_width + platform_width) / 2;
        float combinedHalfHeights = (obj_height + platform_height) / 2;

        // Determine the overlap on both axes
        float overlapX = combinedHalfWidths - std::abs(deltaX);
        float overlapY = combinedHalfHeights - std::abs(deltaY);

        if (overlapX >= overlapY) {
            if (deltaY > 0) { // Collision from above
                obj->SetPosition(Vector2{obj->GetPosition().x, platform_y + platform_height});
                obj->SetVelocity(Vector2{obj->GetVelocity().x, 0});
            } else { // Collision from below
                obj->SetPosition(Vector2{obj->GetPosition().x, platform_y - obj_height});
                obj->SetVelocity(Vector2{obj->GetVelocity().x, 0});
            }
        } else {
            // Toggle direction for MONSTER collisions that occur on the X-axis
            if (obj->type_ == MONSTER) {
                obj->ToggleMovingRight();
            }
            if (deltaX > 0) { // Collision from the left
                obj->SetPosition(Vector2{platform_x + platform_width, obj->GetPosition().y});
                obj->SetVelocity(Vector2{0, obj->GetVelocity().y});
            } else { // Collision from the right
                obj->SetPosition(Vector2{platform_x - obj_width, obj->GetPosition().y});
                obj->SetVelocity(Vector2{0, obj->GetVelocity().y});
            }
        }
    }
}