//
// Created by ben on 8/1/24.
//

#ifndef PLATFORMER_OBSERVER_H
#define PLATFORMER_OBSERVER_H

#endif //PLATFORMER_OBSERVER_H

#include "../../Entities/GameObject.h"
#include "../Events.h"

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const GameObject* entity, Event event) = 0;
};
