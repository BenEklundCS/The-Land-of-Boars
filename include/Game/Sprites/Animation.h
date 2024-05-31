//
// Created by ben on 5/20/24.
//

#ifndef PLATFORMER_ANIMATION_H
#define PLATFORMER_ANIMATION_H

#include "TextureManager.h"

/*
 * The Animation class is responsible for Animating Texture2D objects, by
 * calculating the current rect that should be displayed.
 */
class Animation {
private:
    GameTexture gameTexture_{};
    int currentFrame_;
    float frameTime_;
    int frameCount_;
    float frameDuration_;
    bool replay_;
public:
    Animation(GameTexture gameTexture, int frameCount, float frameDuration, bool replay);
    [[nodiscard]] Texture2D GetTexture() const; // Get the current Texture2D
    [[nodiscard]] Rectangle GetCurrentRect() const; // Get the current animation rect
    void Animate(); // Get the next frame of the animation
    void Reset(); // Reset to the first frame
    void FlipX(bool movingRight); // Flip the animation across the X axis
};


#endif //PLATFORMER_ANIMATION_H
