//
// Created by ben on 1/8/25.
//

#include "../../../include/Utilities/Random.h"

#include <random>
#include <chrono>

/**
 * @brief Gives a random floating-point value between an inclusive range of values
 * @param x The lower bound of the distribution
 * @param y The upper bound of the distribution
 * @returns A random floating-point value between the provided range
 */
float GetRandomFloat(const float x, const float y) {
    // Create a random number generator
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    // Create a uniform distribution between x and y
    std::uniform_real_distribution<float> distribution(x, y);
    return distribution(generator);
}

/**
 * @brief Gives a random integer value between an inclusive range of values
 * @param x The lower bound of the distribution
 * @param y The upper bound of the distribution
 * @returns A random integer value between the provided range
 */
int GetRandomInt(const int x, const int y) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(x, y);
    return distribution(generator);
}
