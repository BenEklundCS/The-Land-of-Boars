//
// Created by ben on 8/1/24.
//

#include "../../../../include/Game/Events/Observers/Subject.h"

void Subject::notify(const GameObject *entity, Event event) {
    for (int i = 0; i < numObservers_; i++)
    {
        observers_[i]->onNotify(entity, event);
    }
}

void Subject::addObserver(Observer *observer) {
    for (int i = 0; i < MAX_OBSERVERS; i++) {
        if (observers_[i] == nullptr) {
            observers_[i] = observer;
            return; // observer has been added successfully
        }
    }
    TraceLog(LOG_ERROR, "Failed to add observer: \n %s",
                        "Observer array has reached max size %i / %i", numObservers_, MAX_OBSERVERS);

}

void Subject::removeObserver(Observer *observer) {

}