//
// Created by ben on 5/20/24.
//



#include "../../../include/Game/Sprites/Animation.h"

/**
 * @brief Constructs an Animation object.
 *
 * @param gameTexture The texture to be used for the animation.
 * @param frameCount The total number of frames in the animation.
 * @param frameDuration The duration (in seconds) for each frame.
 * @param replay Whether the animation should replay after reaching the last frame.
 */
Animation::Animation(const GameTexture &gameTexture, const int frameCount, const float frameDuration, const bool replay) {
    this->gameTexture_ = gameTexture;
    this->currentFrame_ = 0;
    this->frameCount_ = frameCount;
    this->frameDuration_ = frameDuration;
    this->frameTime_ = 0.0f;
    this->replay_ = replay;
}

/**
 * @brief Retrieves the texture used for the animation.
 *
 * @return The texture object.
 */
Texture2D Animation::GetTexture() const {
    return gameTexture_.texture;
}

/**
 * @brief Gets the current frame's source rectangle from the texture.
 *
 * @return Rectangle representing the portion of the texture for the current frame.
 */
Rectangle Animation::GetCurrentRect() const {
    Rectangle sourceRec = gameTexture_.rect;
    sourceRec.x = static_cast<float>(currentFrame_) * sourceRec.width;
    if (gameTexture_.texture.width < 0) { // If the texture is flipped
        sourceRec.x = static_cast<float>(gameTexture_.texture.width) - sourceRec.x - sourceRec.width; // Flip the x coordinate of the source rectangle
    }
    return sourceRec;
}

/**
 * @brief Resets the animation to the first frame.
 *
 * Resets the frame index and the accumulated frame time.
 */
void Animation::Reset() {
    currentFrame_ = 0;
    frameTime_ = 0.0f;
}

/**
 * @brief Advances the animation based on the elapsed frame time.
 *
 * Updates the current frame, looping back to the first frame if replay is enabled.
 */
void Animation::Animate() {
    frameTime_ += GetFrameTime(); // Accumulate the frame time
    // If replay is off and we're at the last frame, stay at the last frame
    if (IsDone()) {
        return;
    }
    else if (frameTime_ >= frameDuration_) {
        currentFrame_ = (currentFrame_ + 1) % frameCount_; // Loop through frames
        frameTime_ -= frameDuration_; // Reduce frameTime_ by frameDuration_ to handle overflow
    }
}

/**
 * @brief Flips the animation horizontally based on movement direction.
 *
 * Adjusts the texture width to flip the source rectangle horizontally.
 *
 * @param movingRight True if the entity is moving right; false otherwise.
 */
void Animation::FlipX(const bool movingRight) {
    if (movingRight) {
        if (gameTexture_.texture.width < 0) {
            gameTexture_.texture.width *= -1;
        }
    }
    else {
        if (gameTexture_.texture.width > 0) {
            gameTexture_.texture.width *= -1;
        }
    }
}

/**
 * @brief Checks if the animation has completed all frames.
 *
 * @return True if the animation is done and does not replay; false otherwise.
 */
bool Animation::IsDone() const {
    return !replay_ && currentFrame_ == frameCount_ - 1;
}
