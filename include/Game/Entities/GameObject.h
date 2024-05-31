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
    MONSTER,
    TILE,
    OTHER
};

// A GameObject contains information about the position, dimensions, and type of the GameObject
// GameObjects are drawable, and updatable with overrides
class GameObject {
protected:
    Vector2 position_{};
    Vector2 dimensions_{};
public:
    GameObjectType type_; // The type of GameObject used for identification in loops
    explicit GameObject(GameObjectType type = OTHER);
    Vector2 GetPosition(); // Get the current position Vector2
    virtual void Update() = 0; // Update the GameObject
    virtual void Draw() = 0; // Draw the GameObject
    virtual void CollideWithPlayer(Player* player);
    Rectangle GetRect(); // Get the current GameObject rect
    virtual ~GameObject(); // Destructor
};

#endif //PLATFORMER_GAMEOBJECT_H
