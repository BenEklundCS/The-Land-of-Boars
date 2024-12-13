//
// Created by ben on 8/1/24.
//

#include "../../../../include/Game/Events/Observers/Observer.h"

/**
 * @brief Called when the subject notifies the observer of an event.
 *
 * This method is meant to be overridden by derived classes to define
 * specific behavior when an event occurs. By default, it does nothing.
 *
 * @param entity The game object that triggered the event.
 * @param event The event that occurred.
 */
void Observer::OnNotify(const GameObject *entity, Events event) {

}

Observer::~Observer() = default;