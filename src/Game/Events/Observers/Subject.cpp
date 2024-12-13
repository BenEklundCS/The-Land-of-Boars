//
// Created by ben on 8/1/24.
//

#include <algorithm>
#include "../../../../include/Game/Events/Observers/Subject.h"

/**
 * @brief Notifies all registered observers about an event.
 *
 * This method iterates through the list of observers and calls their `OnNotify`
 * method, passing the relevant entity and event.
 *
 * @param entity The game object that triggered the event.
 * @param event The event that occurred.
 */
void Subject::Notify(const GameObject *entity, const Events event) {
    for (Observer* o : observers_) {
        if (o != nullptr) {
            o->OnNotify(entity, event);
        }
    }
}

/**
 * @brief Adds an observer to the subject.
 *
 * Observers are notified of events triggered by this subject.
 *
 * @param observer Pointer to the observer to be added.
 */
void Subject::AddObserver(Observer* observer) {
    observers_.push_back(observer);
}

/**
 * @brief Removes an observer from the subject.
 *
 * This method ensures the observer is no longer notified of events.
 *
 * @param observer Pointer to the observer to be removed.
 */
void Subject::RemoveObserver(Observer* observer) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

/**
 * @brief Default destructor for Subject.
 *
 * Cleans up the `Subject` class, ensuring proper resource management.
 */
Subject::~Subject() = default;
