//
// Created by ben on 5/17/24.
//

#ifndef PLATFORMER_RECTANGLE_H
#define PLATFORMER_RECTANGLE_H

#include "../GameObject.h"
#include "../Player/Player.h"

/**
 * @file Rectangle.h
 * @brief Defines the Platform class, which represents a platform in the game.
 *
 * This class defines a platform object with a specified position, size, and color.
 * It provides functionality for drawing and updating the platform during each game frame.
 */

/**
 * @class Platform
 * @brief Represents a platform in the game world.
 *
 * The Platform class inherits from GameObject and handles the behavior of platforms,
 * including their position, size, and rendering. Platforms can be interacted with by
 * the player (e.g., collision detection) and updated each frame.
 */
class Platform : public GameObject {
protected:
    Color color_{}; ///< The color of the platform.

public:
    /**
     * @brief Constructs a Platform object with the specified position, size, and color.
     *
     * Initializes the platform with the given position, dimensions, and color.
     *
     * @param pos_x The x-coordinate of the platform's position.
     * @param pos_y The y-coordinate of the platform's position.
     * @param dim_x The width of the platform.
     * @param dim_y The height of the platform.
     * @param color The color of the platform.
     */
    Platform(float pos_x, float pos_y, float dim_x, float dim_y, Color color);

    /**
     * @brief Updates the platform's state.
     *
     * This method overrides the base class's Update method. Platforms typically do not move,
     * but this method could be used for other updates such as animations or interactions.
     */
    void Update() override;

    /**
     * @brief Draws the platform on the screen.
     *
     * This method overrides the base class's Draw method to render the platform's rectangle
     * using its specified color and dimensions.
     */
    void Draw() override;
};

#endif //PLATFORMER_RECTANGLE_H
