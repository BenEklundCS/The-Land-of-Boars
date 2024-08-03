//
// Created by ben on 8/1/24.
//

#include <algorithm>
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

void Subject::AddObserver(Observer* observer) {
    observers_.push_back(std::unique_ptr<Observer>(observer));
    numObservers_++;
}

void Subject::RemoveObserver(Observer* observer) {
    observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
                                    [&observer](const std::unique_ptr<Observer>& o) {
                                        return o.get() == observer;
                                    }),
                     observers_.end());
}

Subject::~Subject() = default;
