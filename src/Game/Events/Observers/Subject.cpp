//
// Created by ben on 8/1/24.
//

#include <algorithm>
#include "../../../../include/Game/Events/Observers/Subject.h"

void Subject::Notify(const GameObject *entity, const Events event) {
    for (Observer* o : observers_) {
        if (o != nullptr) {
            o->OnNotify(entity, event);
        }
    }
}

void Subject::AddObserver(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

Subject::~Subject() = default;
