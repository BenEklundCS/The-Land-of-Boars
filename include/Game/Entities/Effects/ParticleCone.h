//
// Created by ben on 8/17/24.
//

#ifndef THE_LAND_OF_BOARS_EFFECT_H
#define THE_LAND_OF_BOARS_EFFECT_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"
#include "../../Sprites/Animation.h"

class ParticleCone : public GameObject {
public:
    ParticleCone(Vector2 position, Vector2 playerDimensions, bool facingRight, float particleCount);
    void Update() override;
    void Draw() override;
    bool ShouldRemove() const;
private:
    bool facingRight_;
    float particleCount_;
    bool shouldRemove_ = false;
    Vector2 playerDimensions_{};
    Vector2 position_{};
};

#endif //THE_LAND_OF_BOARS_EFFECT_H
