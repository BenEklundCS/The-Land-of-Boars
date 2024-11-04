#include "../../../include/Game/Entities/CollisionHandler.h"
#include "cmath"
#include "raylib.h"

// Handle an arbitrary platform collision between obj, a moving object
// and platform a stationary platform the object will collide with
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