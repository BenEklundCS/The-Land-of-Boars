//
// Created by ben on 1/8/25.
//

#ifndef THE_LAND_OF_BOARS_RANDOM_H
#define THE_LAND_OF_BOARS_RANDOM_H

/**
 * @brief Gives a random floating-point value between an inclusive range of values
 * @param x The lower bound of the distribution
 * @param y The upper bound of the distribution
 * @returns A random floating-point value between the provided range
 */
float GetRandomFloat(float x, float y);

/**
 * @brief Gives a random integer value between an inclusive range of values
 * @param x The lower bound of the distribution
 * @param y The upper bound of the distribution
 * @returns A random integer value between the provided range
 */
int GetRandomInt(int x, int y);

#endif //THE_LAND_OF_BOARS_RANDOM_H
