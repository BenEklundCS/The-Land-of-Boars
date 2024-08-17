//
// Created by ben on 8/17/24.
//

#include "../../../include/Game/Entities/Effects/ParticleCone.h"
#include "cmath"

ParticleCone::ParticleCone(bool movingRight, float particleCount) {
    facingRight_ = movingRight;
    particleCount_ = particleCount;
}

void ParticleCone::Draw() {
    // Number of particles to draw
    int particles = static_cast<int>(particleCount_);

    // Determine the direction based on whether the object is facing right or left
    float baseAngle = facingRight_ ? 0.0f : PI;

    // Loop through each particle
    for (int i = 0; i < particles; i++) {
        // Randomize the spread within the cone
        float spread = GetRandomValue(-30, 30) * DEG2RAD;
        float angle = baseAngle + spread;

        // Randomize the distance of the particle from the origin
        float distance = GetRandomValue(10, 50);

        // Calculate the particle's position
        Vector2 particlePosition = {
                position_.x + cosf(angle) * distance,
                position_.y + sinf(angle) * distance
        };

        // Draw the particle as a small circle or a texture
        DrawCircleV(particlePosition, 3, WHITE); // You can adjust the size and color as needed
    }
}


void ParticleCone::Update() {
    TraceLog(LOG_INFO, "PARTICLE COUNT %d", particleCount_);
    // Decrease the particle count over time
    particleCount_--;
    if (particleCount_ <= 0) {
        // Mark the effect for removal
        shouldRemove_ = true;
    }
}

bool ParticleCone::ShouldRemove() const {
    return shouldRemove_;
}