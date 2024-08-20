#include "../../../include/Game/Entities/CollisionHandler.h"
#include "cmath"
#include "raylib.h"

// Handle an arbitrary platform collision between obj, a moving object
// and platform a stationary platform the object will collide with
void CollisionHandler::HandlePlatformCollision(GameObject *obj, GameObject *platform) {
    if (CheckCollisionRecs(obj->GetRect(), platform->GetRect())) {
        Rectangle objRect = obj->GetRect();
        Rectangle platformRect = platform->GetRect();

        float deltaX = (objRect.x + objRect.width / 2) - (platformRect.x + platformRect.width / 2);
        float deltaY = (objRect.y + objRect.height / 2) - (platformRect.y + platformRect.height / 2);

        float combinedHalfWidths = (objRect.width + platformRect.width) / 2;
        float combinedHalfHeights = (objRect.height + platformRect.height) / 2;

        // Determine the overlap on both axes
        float overlapX = combinedHalfWidths - std::abs(deltaX);
        float overlapY = combinedHalfHeights - std::abs(deltaY);

        if (overlapX >= overlapY) {
            if (deltaY > 0) { // Collision from above
                obj->SetPosition(Vector2{obj->GetPosition().x, platformRect.y + platformRect.height});
                obj->SetVelocity(Vector2{obj->GetVelocity().x, 0});
            } else { // Collision from below
                obj->SetPosition(Vector2{obj->GetPosition().x, platformRect.y - objRect.height});
                obj->SetVelocity(Vector2{obj->GetVelocity().x, 0});
            }
        } else {
            obj->ToggleMovingRight();
            if (deltaX > 0) { // Collision from the left
                obj->SetPosition(Vector2{platformRect.x + platformRect.width, obj->GetPosition().y});
                obj->SetVelocity(Vector2{0, obj->GetVelocity().y});
            } else { // Collision from the right
                obj->SetPosition(Vector2{platformRect.x - objRect.width, obj->GetPosition().y});
                obj->SetVelocity(Vector2{0, obj->GetVelocity().y});
            }
        }
    }
}