//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_ANIMATION_H
#define PLATFORMER_ANIMATION_H

#include "TextureManager.h"

/**
 * @file Animation.h
 * @brief Manages animations for `Texture2D` objects by calculating and displaying the correct frame rectangles.
 *
 * The `Animation` class allows for smooth animations by cycling through frames of a sprite sheet.
 * It provides features like frame flipping, replay control, and frame duration customization.
 */

/**
 * @class Animation
 * @brief Handles animating sprite sheets for game entities.
 *
 * The `Animation` class is responsible for managing animations by calculating the current frame's rectangle to display.
 * It supports replay, frame flipping, and smooth frame transitions.
 */
class Animation {
private:
    GameTexture gameTexture_; ///< The texture associated with the animation.
    int currentFrame_;        ///< The current frame being displayed.
    float frameTime_;         ///< Time elapsed since the last frame change.
    int frameCount_;          ///< Total number of frames in the animation.
    float frameDuration_;     ///< Duration each frame is displayed (in seconds).
    bool replay_;             ///< Whether the animation should loop.

public:
    /**
     * @brief Constructor for the `Animation` class.
     * @param gameTexture The `GameTexture` containing the sprite sheet and frame data.
     * @param frameCount The total number of frames in the animation.
     * @param frameDuration The duration (in seconds) each frame is displayed.
     * @param replay Whether the animation should loop after completing all frames.
     */
    Animation(const GameTexture &gameTexture, int frameCount, float frameDuration, bool replay);

    /**
     * @brief Retrieves the texture associated with the animation.
     * @return The `Texture2D` object representing the sprite sheet.
     */
    [[nodiscard]] Texture2D GetTexture() const;

    /**
     * @brief Retrieves the rectangle for the current animation frame.
     * @return A `Rectangle` defining the position and size of the current frame in the sprite sheet.
     */
    [[nodiscard]] Rectangle GetCurrentRect() const;

    /**
     * @brief Advances the animation to the next frame based on elapsed time.
     *
     * If the total frame time exceeds the frame duration, the animation advances to the next frame.
     * If `replay_` is `false`, the animation stops at the last frame.
     */
    void Animate();

    /**
     * @brief Resets the animation to the first frame.
     *
     * This can be useful when restarting an animation from the beginning.
     */
    void Reset();

    /**
     * @brief Flips the animation horizontally.
     * @param movingRight Whether the animation should face right (`true`) or left (`false`).
     *
     * Flipping is achieved by inverting the texture's width property.
     */
    void FlipX(bool movingRight);

    /**
     * @brief Checks if the animation has completed.
     * @return `true` if the animation has finished and is not set to replay, otherwise `false`.
     */
    bool IsDone() const;
};

#endif //PLATFORMER_ANIMATION_H
