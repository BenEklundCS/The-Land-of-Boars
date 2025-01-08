//
// Created by ben on 1/8/25.
//

#include "../../../include/Utilities/Random.h"

#include <random>
#include <chrono>

float GetRandomFloat(float x, float y) {
    // Create a random number generator
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    // Create a uniform distribution between x and y
    std::uniform_real_distribution<float> distribution(x, y);
    return distribution(generator);
}

int GetRandomInt(int x, int y) {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(x, y);
    return distribution(generator);
}
