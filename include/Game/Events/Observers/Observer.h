//
// Created by ben on 8/1/24.
//

#ifndef PLATFORMER_OBSERVER_H
#define PLATFORMER_OBSERVER_H

#include "../Events.h"
#include "../../Entities/GameObject.h"


class Observer {
public:
    virtual ~Observer();
    virtual void OnNotify(const GameObject* entity, Events event);
};

#endif //PLATFORMER_OBSERVER_H
