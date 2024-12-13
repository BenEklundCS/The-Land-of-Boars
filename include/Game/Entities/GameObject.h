//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_GAMEOBJECT_H
#define PLATFORMER_GAMEOBJECT_H

#include "raylib.h"

/**
 * @file GameObject.h
 * @brief Base class for all game objects in the platformer game.
 *
 * This abstract class provides common attributes and behavior for
 * game objects, including position, velocity, dimensions, and rendering.
 * GameObjects can be updated and drawn, with specialized behavior implemented
 * in derived classes.
 */

// Forward declaration of Player class
class Player;

/**
 * @brief Enum for identifying the type of GameObject.
 *
 * This enum is used to distinguish between different types of game objects
 * during runtime (e.g., `PLAYER`, `PLATFORM`, etc.).
 */
enum GameObjectType {
    PLAYER,
    PLATFORM,
    MOVING_PLATFORM,
    MONSTER,
    TILE,
    TREE,
    OTHER
};

/**
 * @class GameObject
 * @brief Abstract base class for all game objects in the platformer game.
 *
 * This class provides the core functionality required for game objects,
 * such as position, dimensions, velocity, flashing effects, and removal flags.
 * It serves as a base for more specialized objects like `Player` or `Platform`.
 */
class GameObject {
protected:
    Vector2 position_{}; ///< The position of the object in the game world.
    Vector2 dimensions_{}; ///< The dimensions (width and height) of the object.
    Vector2 velocity_{}; ///< The velocity of the object for movement updates.

    bool flashToggle_ = false; ///< Whether the object is currently flashing.
    bool hasBeenToggled_ = false; ///< Internal state for tracking flash toggling.
    float timeSinceToggle_ = 0.0f; ///< Time since the last flash toggle.
    float timeStepForFlash_ = 0.0f; ///< Time interval for flashing effect.
    Color color_ = WHITE; ///< The color of the object (default is white).
    bool shouldRemove_ = false; ///< Flag indicating if the object should be removed from the scene.
    bool movingRight_ = true; ///< Direction of movement (true if moving right).

    /**
     * @brief Scales the object based on global scaling factors.
     */
    void Scale();

    /**
     * @brief Updates the flashing behavior of the object.
     *
     * This method handles the toggling of the flash state based on
     * elapsed time and the flash interval.
     *
     * @param deltaTime Time elapsed since the last frame.
     */
    void UpdateFlashing(float deltaTime);

public:
    /**
     * @brief Constructor for GameObject.
     *
     * @param type The type of the GameObject (default is `OTHER`).
     */
    explicit GameObject(GameObjectType type = OTHER);

    /**
     * @brief Sets the position of the object.
     *
     * @param newPosition The new position to set.
     */
    void SetPosition(Vector2 newPosition);

    /**
     * @brief Sets the velocity of the object.
     *
     * @param newVelocity The new velocity to set.
     */
    void SetVelocity(Vector2 newVelocity);

    /**
     * @brief Toggles the movement direction of the object.
     *
     * This is typically used for objects that can move left and right (e.g., monsters).
     */
    void ToggleMovingRight();

    /**
     * @brief Gets the current movement direction of the object.
     *
     * @return `true` if moving right, `false` otherwise.
     */
    [[nodiscard]] bool GetMovingRight() const;

    /**
     * @brief Gets the current position of the object.
     *
     * @return The position as a `Vector2`.
     */
    [[nodiscard]] Vector2 GetPosition() const;

    /**
     * @brief Gets the current velocity of the object.
     *
     * @return The velocity as a `Vector2`.
     */
    [[nodiscard]] Vector2 GetVelocity() const;

    /**
     * @brief Gets the current color of the object.
     *
     * @return The color as a `Color`.
     */
    [[nodiscard]] Color GetColor() const;

    /**
     * @brief Toggles the flashing state of the object.
     *
     * This is typically used for visual effects, such as indicating that
     * an object has been hit or is in a special state.
     */
    void ToggleFlashing();

    /**
     * @brief Updates the object.
     *
     * This is a pure virtual function that must be implemented by derived classes
     * to define the object's behavior during each frame.
     */
    virtual void Update() = 0;

    /**
     * @brief Draws the object.
     *
     * This is a pure virtual function that must be implemented by derived classes
     * to define how the object is rendered on the screen.
     */
    virtual void Draw() = 0;

    /**
     * @brief Handles collisions with the player.
     *
     * Derived classes can override this method to define specific collision
     * behavior when interacting with the player.
     *
     * @param player A pointer to the player object.
     */
    virtual void CollideWithPlayer(Player* player);

    /**
     * @brief Gets the rectangle representing the object's bounds.
     *
     * @return The rectangle as a `Rectangle`.
     */
    virtual Rectangle GetRect();

    /**
     * @brief Checks if the object should be removed from the scene.
     *
     * @return `true` if the object should be removed, `false` otherwise.
     */
    [[nodiscard]] virtual bool ShouldRemove() const;

    /**
     * @brief Virtual destructor for GameObject.
     */
    virtual ~GameObject();

    GameObjectType type_; ///< The type of the GameObject (e.g., `PLAYER`, `PLATFORM`).
};

#endif //PLATFORMER_GAMEOBJECT_H
