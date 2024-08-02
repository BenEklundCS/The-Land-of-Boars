//
// Created by ben on 8/1/24.
//

#include "../../../../include/Game/Events/Observers/Subject.h"

void Subject::Notify(const GameObject *entity, Events event) {
    for (int i = 0; i < numObservers_; i++)
    {
        if (observers_[i] != nullptr) {
            TraceLog(LOG_INFO, "%i", i);
            observers_[i]->OnNotify(entity, event);
        }
    }
}

void Subject::AddObserver(Observer *observer) {
    for (auto & i : observers_) {
        if (i == nullptr) {
            i = observer;
            numObservers_++;
            return; // observer has been added successfully
        }
    }
    // We made it to the end of the array, and it's full
    TraceLog(LOG_ERROR, "Failed to add observer: Observer array has reached max size %i / %i", numObservers_, MAX_OBSERVERS);
}

void Subject::RemoveObserver(Observer *observer) {
    for (auto & i : observers_) {
        if (i == observer) {
            i = nullptr;
            numObservers_--;
            return; // Observer has been removed successfully
        }
    }
    // If we reach here, the observer was not found in the array
    TraceLog(LOG_ERROR, "Failed to remove observer: Observer not found");
}

Subject::~Subject() = default;
