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
    std::vector<Observer*> observers_; // _observers array
    int numObservers_ = 0; // number of observers
public:
    void AddObserver(Observer* observer); // Add an Observer to the Subject, allowing the Subject to Notify observers
    void RemoveObserver(Observer* observer); // Removes an Observer from the Subject.
    ~Subject();
protected:
    void Notify(const GameObject* entity, Events event); // Notifies all observers of the object's event
};

#endif //PLATFORMER_SUBJECT_H