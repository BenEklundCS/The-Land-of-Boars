//
// Created by ben on 5/20/24.
//



#include "../../../include/Game/Sprites/Animation.h"

Animation::Animation(GameTexture gameTexture, int frameCount, float frameDuration, bool replay) {
    this->gameTexture_ = gameTexture;
    this->currentFrame_ = 0;
    this->frameCount_ = frameCount;
    this->frameDuration_ = frameDuration;
    this->frameTime_ = 0.0f;
    this->replay_ = replay;
}

Texture2D Animation::GetTexture() const {
    return gameTexture_.texture;
}

Rectangle Animation::GetCurrentRect() const {
    Rectangle sourceRec = gameTexture_.rect;
    sourceRec.x = (float)currentFrame_ * sourceRec.width;
    if (gameTexture_.texture.width < 0) { // If the texture is flipped
        sourceRec.x = gameTexture_.texture.width - sourceRec.x - sourceRec.width; // Flip the x coordinate of the source rectangle
    }
    return sourceRec;
}

void Animation::Reset() {
    currentFrame_ = 0;
    frameTime_ = 0.0f;
}

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

void Animation::FlipX(bool movingRight) {
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

bool Animation::IsDone() const {
    return !replay_ && currentFrame_ == frameCount_ - 1;
}
