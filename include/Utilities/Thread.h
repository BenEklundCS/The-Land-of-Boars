//
// Created by ben on 1/13/25.
//

#ifndef THE_LAND_OF_BOARS_THREAD_H
#define THE_LAND_OF_BOARS_THREAD_H

#include <thread>
#include <chrono>

// Function to call another function asynchronously after a delay
template<typename Func>
void callAfterDelay(Func func, int delayMillis) {
    std::thread([func, delayMillis]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMillis));
        func();
    }).detach(); // Detach the thread to let it run independently
}

#endif //THE_LAND_OF_BOARS_THREAD_H