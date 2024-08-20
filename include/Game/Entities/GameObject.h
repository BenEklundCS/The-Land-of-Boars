//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_GAMEOBJECT_H
#define PLATFORMER_GAMEOBJECT_H

#include "raylib.h"

class Player; // forward declaration, as Player is an instance of GameObject

// Definitions of GameObject types
enum GameObjectType {
    PLAYER,
    PLATFORM,
    MOVING_PLATFORM,
    MONSTER,
    TILE,
    TREE,
    OTHER
};

// A GameObject contains information about the position, dimensions, and type of the GameObject
// GameObjects are drawable, and updatable with overrides
class GameObject {
protected:
    Vector2 position_{};
    Vector2 dimensions_{};
    Vector2 velocity_{};
    void UpdateFlashing(float deltaTime);
    bool flashToggle_ = false;
    bool hasBeenToggled_ = false;
    float timeSinceToggle_ = 0.0f;
    float timeStepForFlash_ = 0.0f;
    Color color_ = WHITE;
    bool shouldRemove_ = false;
    bool movingRight_ = true;
public:
    void SetPosition(Vector2 newPosition);
    void SetVelocity(Vector2 newVelocity);
    void ToggleMovingRight();
    bool GetMovingRight();
    GameObjectType type_; // The type of GameObject used for identification in loops
    explicit GameObject(GameObjectType type = OTHER);
    Vector2 GetPosition(); // Get the current position Vector2
    Vector2 GetVelocity(); // Get the current velocity Vector2
    Color GetColor();
    // Flashing behavior
    void ToggleFlashing();
    virtual void Update() = 0; // Update the GameObject
    virtual void Draw() = 0; // Draw the GameObject
    virtual void CollideWithPlayer(Player* player);
    virtual Rectangle GetRect(); // Get the current GameObject rect
    [[nodiscard]] virtual bool ShouldRemove() const; // Method to check if the object should be removed from the scene
    virtual ~GameObject(); // Destructor

};

#endif //PLATFORMER_GAMEOBJECT_H
