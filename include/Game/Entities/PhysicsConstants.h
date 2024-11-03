//
// Created by ben on 5/26/24.
//

#ifndef PLATFORMER_PHYSICSCONSTANTS_H
#define PLATFORMER_PHYSICSCONSTANTS_H

#include "../../../include/Platform/Globals.h"

// Scale window constants to the scale
#define GRAVITY (45 * WINDOW_SCALE_FACTOR_Y)
#define FRICTION (85 * WINDOW_SCALE_FACTOR_X)
#define MAX_VELOCITY (1000 * WINDOW_SCALE_FACTOR_X)

#endif //PLATFORMER_PHYSICSCONSTANTS_H
