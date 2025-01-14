//
// Created by ben on 12/12/24.
//

#ifndef THE_LAND_OF_BOARS_BUTTON_H
#define THE_LAND_OF_BOARS_BUTTON_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"
#include <functional>

#define BUTTON_WIDTH 240
#define BUTTON_HEIGHT 120

#define BUTTON_IDLE 0
#define BUTTON_HOVER 1
#define BUTTON_PRESSED 2

class Button : public GameObject {
private:
    GameTexture texture_{};
    std::string text_;
    int state_ = BUTTON_IDLE;
    std::function<void()> onClick_;
public:
    Button(Vector2 position, Vector2 dimensions, const std::function<void()>& callback, const std::string& text);
    virtual void ChangeState();
    virtual void HandleAction();
    virtual void Reset();
    void Update() override;
    void Draw() override;
};

#endif //THE_LAND_OF_BOARS_BUTTON_H
