//
// Created by ben on 5/16/24.
//

#ifndef PLATFORMER_WINDOW_H
#define PLATFORMER_WINDOW_H

#define DEFAULT_WINDOW_WIDTH 2560 /**< Default width for the game window. */
#define DEFAULT_WINDOW_HEIGHT 1440 /**< Default height for the game window. */
#define WINDOW_NAME "The Land of Boars" /**< The title displayed on the game window. */

#include <memory>

/**
 * @class Window
 * @brief Manages the game window, including initialization, resizing, and scaling.
 *
 * The `Window` class follows a Singleton design pattern to ensure that only one instance of the game window exists.
 * It handles tasks such as setting up the window, resizing, and initializing scaling factors for consistent rendering across different resolutions.
 */
class Window {
private:
    int windowWidth_ = DEFAULT_WINDOW_WIDTH; /**< The current width of the game window. */
    int windowHeight_ = DEFAULT_WINDOW_HEIGHT; /**< The current height of the game window. */

    /**
     * @brief Initializes scaling factors based on the current window dimensions.
     *
     * This method calculates scaling factors for the game to adapt to different screen sizes and resolutions.
     * It ensures that all rendered elements scale appropriately.
     */
    static void InitScaling();

    static std::unique_ptr<Window> instance; /**< Singleton instance of the `Window` class. */

public:
    /**
     * @brief Constructs the `Window` object and initializes the game window.
     *
     * This constructor sets up the game window using default dimensions and initializes scaling factors.
     * It also sets other window configurations such as frame rate and resizable flag.
     */
    Window();

    /**
     * @brief Resizes the game window to new dimensions.
     *
     * @param window_width The new width of the game window.
     * @param window_height The new height of the game window.
     *
     * This method updates the window dimensions and recalculates scaling factors.
     */
    void Resize(int window_width, int window_height);

    /**
     * @brief Retrieves the singleton instance of the `Window` class.
     *
     * If the instance does not exist, it will be created. This ensures only one `Window` instance exists throughout the game.
     *
     * @return Window* Pointer to the singleton instance of the `Window` class.
     */
    static Window* GetInstance();

    /**
     * @brief Destroys the `Window` object and cleans up resources.
     *
     * This destructor closes the game window and ensures proper cleanup of resources.
     */
    ~Window();
};

#endif //PLATFORMER_WINDOW_H
