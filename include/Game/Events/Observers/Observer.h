//
// Created by ben on 8/1/24.
//

#ifndef PLATFORMER_OBSERVER_H
#define PLATFORMER_OBSERVER_H

#include "../Events.h"
#include "../../Entities/GameObject.h"

/**
 * @class Observer
 * @brief Base class for implementing the Observer pattern.
 *
 * The `Observer` class provides an interface for objects that want to be notified
 * of specific `Events` triggered by observed `Subjects`. Subclasses of `Observer`
 * can implement the `OnNotify` method to define custom behavior in response to these events.
 *
 * This class is part of the Observer design pattern, which decouples event producers
 * (Subjects) from event consumers (Observers), allowing for flexible and modular event handling.
 */
class Observer {
public:
    /**
     * @brief Virtual destructor for `Observer`.
     *
     * Ensures proper cleanup of derived classes when deleted through a pointer to `Observer`.
     */
    virtual ~Observer();

    /**
     * @brief Notification handler called when an observed event occurs.
     *
     * @param entity Pointer to the `GameObject` associated with the event. Can be `nullptr` if the event
     *        does not pertain to a specific object.
     * @param event The `Events` enum value representing the event that occurred.
     *
     * This method should be overridden by subclasses to define specific behavior
     * for different event types.
     */
    virtual void OnNotify(const GameObject* entity, Events event);
};

#endif //PLATFORMER_OBSERVER_H
