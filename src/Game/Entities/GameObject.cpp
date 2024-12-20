//
// Created by ben on 5/17/24.
//

#include "../../../include/Game/Entities/GameObject.h"
#include "../../../include/Platform/Globals.h"
#include "../../../include/Game/Entities/PhysicsConstants.h"

/**
 * @brief Constructs a GameObject with the specified type.
 *
 * Initializes the position and dimensions to (0, 0) and scales the object
 * based on global scaling factors.
 *
 * @param type The type of the GameObject (e.g., PLAYER, MONSTER, PLATFORM, etc.).
 */
GameObject::GameObject(const GameObjectType type)
        : position_{0.0f, 0.0f}, dimensions_{0.0f, 0.0f}, type_(type) {
    Scale();
}

/**
 * @brief Virtual destructor for GameObject.
 */
GameObject::~GameObject() = default;

/**
 * @brief Updates the GameObject's state, including flashing behavior.
 */
void GameObject::Update() {
    const float deltaTime = GetFrameTime();
    UpdateFlashing(deltaTime);
}

/**
 * @brief Retrieves the rectangle representing the GameObject's position and dimensions.
 *
 * @return Rectangle A rectangle with the GameObject's current position and dimensions.
 */
Rectangle GameObject::GetRect() {
    return Rectangle{position_.x, position_.y, dimensions_.x, dimensions_.y};
}

/**
 * @brief Handles collisions with a player. Can be overridden by derived classes.
 *
 * @param player Pointer to the Player object involved in the collision.
 */
void GameObject::CollideWithPlayer(Player *player) {

}

/**
 * @brief Checks if the GameObject should be removed from the game.
 *
 * @return true If the object should be removed; otherwise, false.
 */
bool GameObject::ShouldRemove() const {
    return shouldRemove_;
}

/**
 * @brief Toggles the flashing effect for the GameObject.
 */
void GameObject::ToggleFlashing() {
    if (!hasBeenToggled_) {
        hasBeenToggled_ = true;
        timeSinceToggle_ = 0.0f;
        color_ = RED;
    }
}

/**
 * @brief Updates the flashing behavior of the GameObject.
 *
 * Flashing alternates the object's color between RED and WHITE
 * at a specific time interval and disables flashing after a certain duration.
 *
 * @param deltaTime Time elapsed since the last frame.
 */
void GameObject::UpdateFlashing(float deltaTime) {
    timeSinceToggle_ += deltaTime;
    timeStepForFlash_ += deltaTime;

    if (hasBeenToggled_) {

        if (timeStepForFlash_ > 0.2f) {
            flashToggle_ = !(bool)flashToggle_;
            if (!flashToggle_) {
                color_ = RED;
            } else {
                color_ = WHITE;
            }
            timeStepForFlash_ = 0.0f;
        }

        if (timeSinceToggle_ > 1.0f) {
            hasBeenToggled_ = false;
            color_ = WHITE;
        }
    }
}

/**
 * @brief Gets the current position of the GameObject.
 *
 * @return Vector2 The current position of the GameObject.
 */
Vector2 GameObject::GetPosition() const {
    return position_;
}

/**
 * @brief Gets the current velocity of the GameObject.
 *
 * @return Vector2 The current velocity of the GameObject.
 */
Vector2 GameObject::GetVelocity() const {
    return velocity_;
}

/**
 * @brief Gets the current color of the GameObject.
 *
 * @return Color The current color of the GameObject.
 */
Color GameObject::GetColor() const {
    return color_;
}

/**
 * @brief Sets the position of the GameObject.
 *
 * @param newPosition The new position for the GameObject.
 */
void GameObject::SetPosition(const Vector2 newPosition) {
    position_ = newPosition;
}

/**
 * @brief Sets the velocity of the GameObject.
 *
 * @param newVelocity The new velocity for the GameObject.
 */
void GameObject::SetVelocity(const Vector2 newVelocity) {
    velocity_ = newVelocity;
}

/**
 * @brief Toggles the direction of movement for the GameObject.
 */
void GameObject::ToggleMovingRight() {
    movingRight_ = !movingRight_;
}

/**
 * @brief Checks if the GameObject is currently moving to the right.
 *
 * @return true If the GameObject is moving right; otherwise, false.
 */
bool GameObject::GetMovingRight() const {
    return movingRight_;
}

/**
 * @brief Scales the GameObject's dimensions and position based on the global window scale factors.
 */
void GameObject::Scale() {
    //TraceLog(LOG_INFO, "Scaling object to %d %d", WINDOW_SCALE_FACTOR_X, WINDOW_SCALE_FACTOR_Y);
    // Adjust the dimensions of the object based on the window scale factor
    dimensions_.x *= WINDOW_SCALE_FACTOR_X;
    dimensions_.y *= WINDOW_SCALE_FACTOR_Y;
    // Adjust the position of the object based on the window scale factor
    position_.x *= WINDOW_SCALE_FACTOR_X;
    position_.y *= WINDOW_SCALE_FACTOR_Y;
}

/**
* @brief Applies gravity to the object's velocity.
*
* This method adjusts the object's velocity by applying gravity based on the delta time.
* Note: The velocity is pre-modified with deltaTime, do not multiply it again later.
* @param deltaTime The time delta for smooth movement.
*/
void GameObject::ApplyGravity() {
    velocity_.y += GRAVITY;
}

/**
* @brief Gets the object's type. Types are defined in GameObjectType enum.
*
* @return The type of the object.
*/
GameObjectType GameObject::GetType() const {
    return type_;
}



