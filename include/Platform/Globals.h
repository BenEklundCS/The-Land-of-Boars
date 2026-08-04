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
 * @brief Screen-space scaling factors and camera helpers.
 *
 * @note RESOLUTION MODEL
 *
 * World data is resolution-independent. Entity positions, dimensions, tile
 * coordinates and physics constants are expressed in fixed **world units** and
 * are never multiplied by a scale factor. Resolution is handled entirely by
 * `Camera2D::zoom` (see `GameStateManager::InitCamera`), which scales the world
 * at render time.
 *
 * This replaced an earlier scheme where `GameObject::Scale()` multiplied every
 * entity's position and dimensions by the window factor. That baked the display
 * resolution into the simulation, so any world literal that forgot to scale
 * silently desynced from the tile grid, and the non-uniform X/Y factors
 * distorted world geometry with the window's aspect ratio.
 *
 * The `WINDOW_SCALE_FACTOR_*` values below are therefore for **screen space
 * only** - UI font sizes and HUD layout. Do not multiply world coordinates,
 * dimensions, velocities or physics constants by them.
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

/**
 * @brief The zoom the world camera should use for the current window.
 *
 * Derived from height alone so the zoom is uniform - using separate X and Y
 * factors is what distorted world geometry under the old scheme. A taller
 * window shows the same vertical slice of the world; a wider window simply
 * sees further horizontally.
 */
inline float GetWorldCameraZoom() {
    return static_cast<float>(GetScreenHeight()) / BASE_SCREEN_HEIGHT;
}

/**
 * @brief The world-space rectangle currently visible through a camera.
 *
 * Anything positioning itself relative to the viewport (background, HUD, FPS
 * counter) must go through this rather than assuming `screen size == world
 * size`, which is only true at zoom 1.
 */
inline Rectangle GetCameraWorldView(const Camera2D &camera) {
    const float w = static_cast<float>(GetScreenWidth()) / camera.zoom;
    const float h = static_cast<float>(GetScreenHeight()) / camera.zoom;
    return Rectangle{
        camera.target.x - camera.offset.x / camera.zoom,
        camera.target.y - camera.offset.y / camera.zoom,
        w, h
    };
}

#endif //GLOBALS_H
