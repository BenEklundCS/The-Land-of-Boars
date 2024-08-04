//
// Created by ben on 8/1/24.
//

#ifndef PLATFORMER_SUBJECT_H
#define PLATFORMER_SUBJECT_H

#define MAX_OBSERVERS 4096

#include <vector>
#include <memory>
#include "Observer.h"

class Subject {
private:
    // This should be a smarter array in final implementation
    std::vector<Observer*> observers_;
    int numObservers_ = 0;
public:
    void AddObserver(Observer* observer);
    void RemoveObserver(Observer* observer);
    ~Subject();
protected:
    void Notify(const GameObject* entity, Events event);
};

#endif //PLATFORMER_SUBJECT_H