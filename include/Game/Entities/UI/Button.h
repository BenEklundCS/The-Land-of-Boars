//
// Created by ben on 12/12/24.
//

#ifndef THE_LAND_OF_BOARS_BUTTON_H
#define THE_LAND_OF_BOARS_BUTTON_H

#include "../GameObject.h"
#include "../../Sprites/TextureManager.h"
#include <functional>

#define BUTTON_WIDTH (int)GetScreenWidth()/4
#define BUTTON_HEIGHT (int)GetScreenHeight()/12

/**
 * @enum ButtonState
 * @brief Represents the various states a button can be in.
 */
enum ButtonState {
    BUTTON_IDLE,   ///< The button is idle and not interacted with.
    BUTTON_HOVER,  ///< The mouse is hovering over the button.
    BUTTON_PRESSED ///< The button is clicked/pressed.
};

/**
 * @class Button
 * @brief Represents a UI button in the game.
 *
 * This class handles rendering a button, detecting user interaction,
 * and executing a callback function when the button is clicked.
 */
class Button : public GameObject {
private:
    GameTexture texture_; ///< The texture used to render the button.
    std::string text_; ///< The text displayed on the button.
    ButtonState state_ = BUTTON_IDLE; ///< The current state of the button.
    std::function<void()> onClick_; ///< Callback function to execute when the button is clicked.
    std::function<void()> onHover_;
    Color color_{};

public:
    /**
     * @brief Constructs a Button object.
     *
     * @param position The position of the button on the screen as a Vector2.
     * @param dimensions The width and height of the button as a Vector2.
     * @param callback The function to call when the button is clicked.
     * @param text The text to display on the button.
     */
    Button(Vector2 position, Vector2 dimensions, std::function<void()> onClick, std::function<void()> onHover, const std::string& text);

    /**
     * @brief Updates the button's state based on user interaction.
     */
    virtual void ChangeState();

    /**
     * @brief Executes the button's action when it is pressed.
     */
    virtual void HandleAction();

    /**
     * @brief Resets the button's state to idle.
     */
    virtual void Reset();

    void SetColor(Color color);

    /**
     * @brief Updates the button's logic every frame.
     *
     * Handles state changes, executes actions, and resets the state.
     */
    void Update() override;

    /**
     * @brief Renders the button on the screen.
     */
    void Draw() override;
};

#endif //THE_LAND_OF_BOARS_BUTTON_H
