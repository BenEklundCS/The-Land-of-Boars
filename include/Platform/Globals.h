//
// Created by ben on 11/3/2024.
//

#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"

// Base screen resolution used as the standard for scaling calculations
#define BASE_SCREEN_WIDTH 2560 /**< The width of the base resolution in pixels (2560px, corresponding to 1440p). */
#define BASE_SCREEN_HEIGHT 1440 /**< The height of the base resolution in pixels (1440px, corresponding to 1440p). */

/**
 * @file Globals.h
 * @brief Provides global constants and scaling factors for the game.
 *
 * This file contains global variables and macros used for scaling and managing the game's resolution.
 * It assumes the base resolution is 2560x1440p and calculates scaling factors dynamically to
 * support other resolutions.
 *
 * @note All hardcoded values in the project are tested and tuned for the base screen size
 * (2560x1440p) and then scaled appropriately.
 */

/**
 * @var WINDOW_SCALE_FACTOR_X
 * @brief Represents the scaling factor for the window's width.
 *
 * This value is calculated dynamically based on the current screen width divided by the base screen width.
 */
inline float WINDOW_SCALE_FACTOR_X;

/**
 * @var WINDOW_SCALE_FACTOR_Y
 * @brief Represents the scaling factor for the window's height.
 *
 * This value is calculated dynamically based on the current screen height divided by the base screen height.
 */
inline float WINDOW_SCALE_FACTOR_Y;

/**
 * @var INVERSE_WINDOW_SCALE_FACTOR_X
 * @brief Represents the inverse of the width scaling factor.
 *
 * Useful for calculations that need to revert scaling adjustments for specific elements or coordinates.
 */
inline float INVERSE_WINDOW_SCALE_FACTOR_X;

/**
 * @var INVERSE_WINDOW_SCALE_FACTOR_Y
 * @brief Represents the inverse of the height scaling factor.
 *
 * Useful for calculations that need to revert scaling adjustments for specific elements or coordinates.
 */
inline float INVERSE_WINDOW_SCALE_FACTOR_Y;

#endif //GLOBALS_H
