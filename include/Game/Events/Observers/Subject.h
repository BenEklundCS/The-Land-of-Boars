//
// Created by ben on 8/1/24.
//

#ifndef PLATFORMER_SUBJECT_H
#define PLATFORMER_SUBJECT_H

#define MAX_OBSERVERS 4096

#include <vector>
#include <memory>
#include "Observer.h"

/**
 * @class Subject
 * @brief Base class for implementing the Subject role in the Observer pattern.
 *
 * The `Subject` class is responsible for maintaining a list of `Observer` instances
 * and notifying them of events. Observers can be added or removed dynamically,
 * enabling modular and decoupled event handling.
 *
 * This class works in conjunction with `Observer` to implement the Observer design pattern.
 * It enables a one-to-many relationship, where a single `Subject` can notify multiple `Observers`
 * of changes or events.
 */
class Subject {
private:
    std::vector<Observer*> observers_; ///< List of observers registered with the subject.

public:
    /**
     * @brief Adds an `Observer` to the list of registered observers.
     *
     * @param observer Pointer to the `Observer` instance to be added.
     *        The observer will receive notifications from this subject.
     */
    void AddObserver(Observer* observer);

    /**
     * @brief Removes an `Observer` from the list of registered observers.
     *
     * @param observer Pointer to the `Observer` instance to be removed.
     *        The observer will no longer receive notifications from this subject.
     */
    void RemoveObserver(Observer* observer);

    /**
     * @brief Virtual destructor for `Subject`.
     *
     * Ensures proper cleanup of derived classes. Observers are not automatically removed,
     * so ensure to clean up manually if required.
     */
    virtual ~Subject();

protected:
    /**
     * @brief Notifies all registered observers of an event.
     *
     * @param entity Pointer to the `GameObject` associated with the event.
     *        Can be `nullptr` if the event is not tied to a specific object.
     * @param event The `Events` enum value representing the event that occurred.
     *
     * This method is called internally by the `Subject` when an event occurs.
     */
    void Notify(const GameObject* entity, Events event);
};

#endif //PLATFORMER_SUBJECT_H
